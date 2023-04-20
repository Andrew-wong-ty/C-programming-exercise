#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 1024

enum States {
    S0 = 0,
    S1, S2, S3, S4, S5, S6
};
typedef struct
{
    char buf[BUFFER_SIZE];
    int ptr; // 指向最后一个元素+1的位置
} Buffer;

int initBuffer(Buffer *buffer) {
    buffer->ptr = 0;
    memset(buffer->buf, '\0', BUFFER_SIZE);
}
int appendBuffer(Buffer *buffer, char c) {
    buffer->buf[buffer->ptr++] = c;
}
int isBufferEmpty(Buffer *buffer){
    if (buffer->ptr==0) return 1;
    else return 0;
}

int main(int argc, char const *argv[])
{
    const char* inputFile= "./intro.c"; 
    const char* outputFile = "./intro-no-comment.c";

    size_t sizeOfBuffer = sizeof(Buffer);
    Buffer* buffer = malloc(sizeof(Buffer));
    initBuffer(buffer);
    
    int res;
    printf("open: %s, generate file: %s \n", inputFile, outputFile);
    FILE* inputFp = fopen(inputFile,"r");
    if(inputFile==NULL) {
        printf("open file %s failed!", inputFile);
    }
    
    FILE* outFp = fopen(outputFile, "w");
    int c;
    enum States currState = S0; 
    enum States lastState = S0; 
    while((c = getc(inputFp))!=EOF) {
        switch (currState)
        {
            case S0:
            {
                lastState = currState;
                if (c=='\"') {
                    currState = S1;
                    putc(c, outFp);
                } else if (c=='\'')
                {
                    currState = S2;
                    putc(c, outFp);
                } else if (c=='/')
                {
                    currState = S3;
                    appendBuffer(buffer,c);
                } else {
                    putc(c, outFp);
                }
                break;
            }

            case S1:
            {
                lastState = currState;
                putc(c, outFp);
                if (c=='\"') {
                    currState = S0;
                } else {
                    currState = S1;
                }
                break;
            }

            case S2:
            {
                lastState = currState;
                putc(c, outFp);
                if (c=='\'') {
                    currState = S0;
                } else {
                    currState = S2;
                }
                break;
            }

            case S3:
            {
                lastState = currState;
                appendBuffer(buffer,c);
                if (c=='/') {
                    currState = S6;
                } else if (c=='*')
                {
                    currState = S4;
                } else {
                    // 非注释
                    currState = S0;
                }
                break;
            }

            case S4:
            {
                lastState = currState;
                appendBuffer(buffer,c);
                if (c=='*') {
                    currState = S5;
                } else {
                    currState = S4;
                }
                break;
            }

            case S5:
            {
                lastState = currState;
                appendBuffer(buffer,c);
                if (c=='/') {
                    currState = S0;
                } else {
                    currState = S4;
                }
                break;
            }

            case S6:
            {
                lastState = currState;
                appendBuffer(buffer,c);
                if (c=='\n') {
                    currState = S0;
                } else {
                    currState = S6;
                }
                break;
            }
        
            default:
                break;
        }
        if (currState==S0 && !isBufferEmpty(buffer)) {
            if (lastState==S3) {
                // 把buffer中的写入
                for(int i = 0;i<buffer->ptr;i++) {
                    putc(buffer->buf[i], outFp);
                }
                initBuffer(buffer);
            } else if (lastState==S6) {
                putc('\n', outFp);
                initBuffer(buffer);
            } else if (lastState==S5) {
                initBuffer(buffer);
            }
        }
    }
    
    printf("Done! \n");

    res = fclose(inputFp);
    res = fclose(outFp);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 128 
static int buffer_pointer = 0; // 指向buffer中的next free pos
static int io_buffer[BUFFER_SIZE];

/*
 * 从input中读取下一个字符
*/
int getch(void) {
    if(buffer_pointer==0) {
        // buffer中没有待回退字符, 读取下一个字符
        return getchar();
    } else {
        return io_buffer[--buffer_pointer];
    }
}

/*
 * 把字符c放进buffer中, 下次读就读到这个
 * e.g. ABC是某个标志的结束符, 因此要读完ABC才能最终判断是否读到了标志
 * 且ABC需要重新处理. |A,B,C| 这应该用一个队列才对...
*/
void ungetch(int c) {
    if (buffer_pointer>=BUFFER_SIZE) {
        // 超过了大小
        printf("ungetch, buffer overflow\n");
    } else {
        io_buffer[buffer_pointer++] = c;
    }

}

/*
 * 从input中读取下一个单词
*/
int getword(char* buffer, int n) {
    // 首先skip所有的空格和\t
}

/*字符比较*/
int myStrcmp(char *str1, char *str2)
{
    while(*str1==*str2) {
        if(*str1=='\0') return 0;
        str1++;
        str2++;
    }
    return *str1-*str2;
}

unsigned myStrlen(char* target) {
    unsigned res = 0;
    while(*target++!='\0') {
        res+=1;
    }
    return res;
}

/*把块作用域内的char[SIZE] 转移到内存，从而能一直存放*/
char* strdup(char* target) {
    char* p = (char*)malloc(myStrlen(target)+1);
    char* curr = p;
    while(*target!='\0') {
        *curr = *target;
        curr++;
        target++;
    }
    *curr = '\0';
    return p;
}
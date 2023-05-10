/*
程序的作用: 在控制台读取多行, 
程序使用快速排序来对行来进行排序

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINES 20
#define MAX_LINE_SIZE 256
// char *textLines[MAX_LINES]; // 一个数组, 大小为MAX_LINES, 里面装的是char指针
extern char *alloc(int n);

void myStrcpy(char *from, char *to)
{
    // C 是值传参, 指针被复制了指向了同一个空间
    while (*from != '\0')
    {
        *to++ = *from++; // 这里相当于*to, 然后to++
    }
    *to = '\0';
}

/*
    若str1==str2: 返回0, str1>str2返回>0, 否则返回<0
*/
int cmp(char *str1, char *str2)
{
    while(*str1==*str2) {
        if(*str1=='\0') return 0;
        str1++;
        str2++;
    }
    return *str1-*str2;
}

/**
 * @brief  读取输入流中的一行
 * @retval None
 */
int getLine(char *buffer)
{
    int c;
    int lineLength = 0;
    while ((c = getchar()) != EOF && lineLength < MAX_LINE_SIZE - 1)
    {
        if (c == '\n')
        {
            break;
        }
        else
        {
            *buffer = c;
            buffer++;
            lineLength++;
        }
    }
    *buffer = '\0';
    return lineLength + 1;
}
/**
 * @brief  在控制台读取n行字符串到textLines中
 * @param  textLines: 存储字符串
 * @param  nLines: 行数
 * @retval
 */
int readLines(char *textLines[], int nLines)
{
    int i = 0;

    int currLineLength;
    while (i < nLines && i < MAX_LINES)
    {
        char currLineBuffer[MAX_LINE_SIZE];
        char *p;
        if ((currLineLength = getLine(currLineBuffer)) != 0)
        {

            printf("Line read: %s\n", currLineBuffer);
            // p = alloc(currLineLength);
            p = (char*)malloc(currLineLength);
            myStrcpy(currLineBuffer, p); // todo 校验大小有没有超
            textLines[i++] = p;          // todo 为什么textLines[i++]直接指向currLineBuffer不行?
        }
    }
    return i; // 返回分配了多少行
}


/**
 * @brief  把n行写到控制台
 * @param  textLines: 存储字符串
 * @param  nLines: 行数
 * @retval
 */
void writeLines(char *textLines[], int nLines)
{
    int i = 0;
    while (i < nLines)
    {
        printf("Line %d: %s\n", i + 1, textLines[i]);
        i++;
    }
}

void swap(char**a, char**b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

char** partition(char**left, char**right) 
{
    char* key = *right; // 以右边为pivot
    char** i = left;
    for(char**j = left;j<right;j++) {
        if(cmp(*j,key)<=0) {
            swap(i,j);
            i++;
        }
    }
    swap(i,right);
    return i;
}

/**
 * @brief  对一个字符串数组进行排序
 * @param  textLines: 字符串数组
 * @param  base: base
 * @param  size: base的偏移
 * @retval None
 */
void myQsort(char** left, char** right)
{
    if(right<=left) return;
    char** pivot = partition(left, right);
    myQsort(left, pivot-1);
    myQsort(pivot+1, right);
}

int main(int argc, char const *argv[])
{
    // int nLines = readLines(textLines, 5);
    char*textLines[] = {"7","6","1","4","0","3"};
    int nLines = 6;
    myQsort(textLines, textLines+nLines-2);
    writeLines(textLines, nLines);
    for (int i = 0; nLines && i < nLines; i++)
    {
        char* p = *(textLines+i);
        free(p);
    }

    return 0;
}

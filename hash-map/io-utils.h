#ifndef __IO_UTILS_H__
#define __IO_UTILS_H__ 1

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 128 
static int buffer_pointer = 0; // 指向buffer中的next free pos
static int io_buffer[BUFFER_SIZE];

/*
 * 从input中读取下一个字符
*/
int getch(void);

/*
 * 把字符c放进buffer中, 下次读就读到这个
 * e.g. ABC是某个标志的结束符, 因此要读完ABC才能最终判断是否读到了标志
 * 且ABC需要重新处理. |A,B,C| 这应该用一个队列才对...
*/
void ungetch(int );

/*
 * 从input中读取下一个单词
*/
int getword(char* , int );

/*字符比较*/
int myStrcmp(char *, char *);

unsigned myStrlen(char* );

/*把块作用域内的char[SIZE] 转移到内存，从而能一直存放*/
char* strdup(char* );

#endif
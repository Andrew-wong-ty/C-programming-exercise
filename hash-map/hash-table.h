#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__ 1

#include<stdio.h>
#include<stdlib.h>
#include "io-utils.h"
#define HASH_SIZE 101

extern int myStrcmp(char *, char *); //io-utils.c
extern char* strdup(char*);

typedef struct hnode
{
    struct hnode* next; // 哈希表可能有冲突，冲突使用链来解决
    char* key; // 需要单独释放内存
    char* value; // 需要单独释放内存
} HashNode;

typedef struct { 
    unsigned size;
    HashNode** hashTable;
} HashTable;

/*在内存中分配一个哈希表*/
HashTable* newHashTable(unsigned);

/*释放哈希表占用的内存空间*/
int deleteHashTable(HashTable*);

unsigned hash(unsigned tableSize, char*s);

/*在哈希表中查找是否有key*/
HashNode* lookup(HashTable* hashTable, char* key);

/*put (key, value) into hashTable*/
HashNode* install(HashTable* hashTable, char* key, char* value);

/*delete (key) in hashTable*/
/*return 1 hashNode if successed else 0*/
int uninstall(HashTable* hashTable, char* key);



/*print the whole hashTable*/
void printHashTable(HashTable* hashTable);

#endif
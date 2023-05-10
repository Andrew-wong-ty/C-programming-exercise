#include<stdio.h>
#include<stdlib.h>
#include "hash-table.h"
#define LIST_HEAD_NOTE "_HEAD_"

#define HASH_SIZE 101

HashTable* newHashTable(unsigned size) {
    if (size<=0) {
        printf("invalid size!\n");
        return NULL;
    }
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    // 存放size个HashNode
    table->hashTable = (HashNode**) malloc(size*sizeof(HashNode*));
    // 初始化
    for (int i = 0; i < size; i++) {
        table->hashTable[i]=(HashNode*)malloc(sizeof(HashNode));
        table->hashTable[i]->next = NULL;
        // table->hashTable[i]->key = LIST_HEAD_NOTE;
        // table->hashTable[i]->value = LIST_HEAD_NOTE;
        table->hashTable[i]->key = strdup(LIST_HEAD_NOTE);
        table->hashTable[i]->value = strdup(LIST_HEAD_NOTE);
    }
    return table;
}

int deleteHashTable(HashTable* hashTable) {
    // 遍历table的每个slot，slot中的每个链，每个链中的HashNode来释放NodeR
    HashNode** table = hashTable->hashTable;
    for (unsigned i = 0; i < hashTable->size; i++)
    {
        HashNode* curr = table[i];
        HashNode* next = NULL;
        while(curr!=NULL) {
            next = curr->next;
            // 释放key-value字符串
            free((void*)curr->key);
            free((void*)curr->value);
            // 释放整个HashNode
            free((void*)curr);
            curr = next;
        }
        table[i] = NULL;
    }
    // 释放完node, 释放HashTable **
    free((void*)table);
    // 释放整个hashTable对象
    free((void*)hashTable);
    return 1;
}

unsigned hash(unsigned tableSize,  char*s) { //unsigned 就表示unsigned int
    return 0; // 测试：把所有node都放到一个地方
    static int randomN = 16;
    unsigned hashValue = 0;
    while(*s!='\0') {
        hashValue= *s+randomN*hashValue;
        s++;
    }
    return hashValue%tableSize;
}

/*在哈希表中查找是否有key, at the same time retrive prev element*/
static HashNode* _lookup_(HashTable* hashTable, char* key, HashNode** prev) {
    HashNode** table = hashTable->hashTable;
    HashNode* curr;
    unsigned hashValue = hash(hashTable->size, key);
    curr = table[hashValue];
    *prev = curr;
    for(;curr!=NULL;*prev = curr ,curr = curr->next) {
        if(myStrcmp(key,curr->key)==0) {
            return curr;
        }
    }
    return NULL;
}

/*get key from hashTable*/
HashNode* lookup(HashTable* hashTable, char* key) {
    HashNode** temp;
    return _lookup_(hashTable, key, temp);
}

/*put (key, value) into hashTable*/
HashNode* install(HashTable* hashTable, char* key, char* value) {
    HashNode* res = NULL;
    HashNode** prev = (HashNode**) malloc(sizeof(HashNode)); // a pointer to search result's previous element
    unsigned hashValue;
    /*hash key doesn't exist*/
    if((res = _lookup_(hashTable,key,prev))==NULL ) {
        printf("new!\n");
        hashValue = hash(hashTable->size, key);
        res = (HashNode*)malloc(sizeof(HashNode));
        res->key = strdup(key);
        res->value = strdup(value);
        res->next = NULL;
        (*prev)->next = res;
        // res->next = hashTable[hashValue]; // 链接上
        // hashTable[hashValue] = res;
    } else {
        /*更新value*/
        printf("replace!\n");
        free((void*)res->value);
        res->value = strdup(value);
    }
    free((void*)prev);
    return res;
}

/*delete (key) in hashTable*/
/*return the deleted hashNode if successed else NULL*/
int uninstall(HashTable* hashTable, char* key) {
    HashNode* res = NULL;
    HashNode** prev;
    unsigned hashValue = hash(hashTable->size, key);
    if((res = _lookup_(hashTable,key,prev))!=NULL ) {
        (*prev)->next = res->next;
        // 释放res
        free((void*)res->key);
        free((void*)res->value);
        free((void*)res);
        return 1;
    } else {
        return 0;
    }
}

/*print the whole hashTable*/
void printHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++)
    {
        if(hashTable->hashTable[i]!=NULL)
            printf("%d: key:%s, value:%s\n",i, hashTable->hashTable[i]->key, hashTable->hashTable[i]->value);
        else
            printf("%d: NULL\n",i);
    }
}
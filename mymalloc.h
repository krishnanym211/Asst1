
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef mymalloc_h
#define mymalloc_h

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

static char myBlock[4096];

typedef struct Node{
    
}

typedef struct metadata{
    struct Node* next;
    int size;
    char inUse;
}metadata;

#endif

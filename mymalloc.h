#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#ifndef mymalloc_h
//#define mymalloc_h

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

//#endif

void* mymalloc(int size, char* file, int line);

static char myBlock[4096];

typedef struct metadata{
    void* ptr;
    int size;
    char inUse;
    struct metadata* next;
}metadata;

//Function definitions

void* mymalloc(int size, char* file, int line);

void myfree(void* toFree, char* file, int line);




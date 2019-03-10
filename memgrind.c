#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

int main (int argc, char** argv){
    printf("sizeof metadata %d\n", sizeof(metadata));
    printf("Start of block: %d\n", myBlock);
    int* i = 0;
    i = (int*)malloc(sizeof(int)*10);
    printf("Pointer returned on first alloc: %d\n",i);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "mymalloc.h"

//malloc() 1 byte and immediately free it - do this 150 times
void testA(){
    int count = 0;
    int total = 0;
    while (count < 100){
        clock_t start = clock(), diff;
        int i;
        for(i = 0;i < 150; i++){
            char * input = (char *) malloc(sizeof(char));
            free(input);
        }
        diff = clock() - start;
        total += diff;
        count++;
    }
    return total/100;
}

//malloc() 1 byte, store the pointer in an array - do this 150 times.
//Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
void testB(){
    int count = 0;
    int total = 0;
    while (count < 100){
        clock_t start = clock(), diff;
        char * inputs[150];
        int i;
        for (i = 0;i<150;i++){
            inputs[i] = (char *) malloc(1);
            if (inputs[i] == NULL){
                return -1;
            }
        }
        int j;
        for (j = 0;j<150;j++){
            free(inputs[j]);
        }
        diff = clock() - start;
        total+=diff;
        count++;
    }
    return total/100;
}

//Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer
void testC(){
    int count = 0;
    int total = 0;
    srand(time(NULL));
    int mallocCounter = 0;
    char* input[4096];
    while (count < 100){
        clock_t start = clock(), diff;
        
        int r = rand()%2;
        int mallocindex = 0;
        int freeindex = 0;
        while(mallocCounter < 50){
            if(r == 0){
                //perform malloc
                
                mallocCounter++;
            }else{
                //perform free
                
            }
        }
    }
    return total/100;
}
void testD(){
	return;
}
void testE(){
	return;
}
void testF(){
	return;
}

int main (int argc, char** argv){
    printf("sizeof metadata %d\n", sizeof(metadata));
    printf("Start of block: %d\n", myBlock);
    int* i = 0;
    i = (int*)malloc(10);
    printf("Pointer returned on first alloc: %d\n",i);
    return 0;
}

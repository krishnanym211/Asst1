#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

metadata* front;
short firstMalloc = 1;

//returns the last index of the block called on
//returns index of block
int currIndex(metadata* block){
    metadata* temp = front;
    int data = 0;
    //while the current block is not the block to count till
    while(temp != block){
        //count the structure size and data block size, adding them
        data += sizeof(metadata) + (*temp).size;
        temp = (*temp).next;
    }
    //return index of the first byte of block
    return data;
}

/*//merges two or 3 consecutiive free blocks into 1
void merge (){
    metadata* temp = front;
    metadata* prev;
    while ((*temp).next != NULL){
        if((*prev).inUse == 'n' && ((*temp).inUse == 'n'){
            (*prev).size += (*temp).size + sizeof(metadata));
            (*prev).next = (*temp).next;
        }
        prev = temp;
        temp = (*temp).next;
    }
    merge();
    return;
}*/

void* mymalloc(int size, char* file, int line){

    mallocErr = 0;
    //if allocation size is equal to or less than 0, thats not valid
    if(size <= 0){
        fprintf(stderr,"ERROR: Must allocate more than 0 bytes\n");
        mallocErr = 1;
        return NULL;
    }
    if(size + sizeof(metadata) > 4096){
        fprintf(stderr,"ERROR: Not enough for allocation\n");
        mallocErr = 1;
        return NULL;
    }
    
    //incase this is the first time malloc has been called
    if(firstMalloc == 1){
        printf("First malloc\n");
        front = (metadata*)myBlock;
        (*front).inUse = 'y';
        (*front).size = size;
        (*front).ptr = &myBlock[(sizeof(metadata))];
        //allocation = &myBlock[(sizeof(metadata))];
        //spaceUsed = sizeof(metadata)+size;

        //initialize newBlock, which is the next block (empty and not in use)
        
        metadata* newBlock;
        newBlock = (metadata*)(&myBlock[sizeof(metadata) + size]);
        (*newBlock).ptr = &myBlock[size + 2*sizeof(metadata)];
        (*newBlock).size = 4096 - (size + 2*sizeof(metadata));
        (*newBlock).inUse = 'n';
        //necessary - cannot guarantee it will be NULL upon initialization
        (*newBlock).next = NULL;

        (*front).next = newBlock;

        firstMalloc = 0;
        mallocErr = 0;
        
        return (*front).ptr;
    }
    
    metadata* temp = front;
    metadata* prev;
    
    while(temp != NULL) {
        
        if((*temp).inUse == 'n' && (*temp).size >= size){

            //incase current block exactly fits size of reuested amount
            if((*temp).size == size){
                printf("Found memory block of exact fit\n");
                (*temp).inUse = 'y';
                mallocErr = 0;
                (*temp).ptr = &myBlock[currIndex(temp) + sizeof(metadata)];
                return (*temp).ptr;
            }
            
            //size of temp block is greater than size of requested alloc

            // if we are within sizeOfMinimumBlock ( i.e. sizeof(metadata) + 1) of the end of the array,
            // we should allocate temp - there is no better fit
            // implement this if statement

            // if(currIndex(temp) + sizeof(metadata)*2 + size + 1 > 4096){

            // }

            //incase first fit block is bigger than the size requested
            //after requested block is allocated, create newBlock to fill space
            if((*temp).size >= (size + sizeof(metadata) + 1)){
                //create new block and fill structure
                metadata* newBlock = (metadata*)(&myBlock[currIndex(temp)+sizeof(metadata)+size]);
                (*newBlock).next = (*temp).next;
                (*temp).ptr = &myBlock[currIndex(temp) + sizeof(metadata)];
                (*temp).next = newBlock;
                (*temp).inUse = 'y';
                //subtract the size of the space requested and metadata from previous size to find the size of new block
                (*newBlock).size = ((*temp).size - size - sizeof(metadata));
                (*temp).size = size;
                //how do i knwo the size of the memory for the new block. calculate each time?
                (*newBlock).inUse = 'n';
                (*newBlock).ptr = &myBlock[currIndex(newBlock)+sizeof(metadata)];
                mallocErr = 0;
                return (*temp).ptr;
            }
        }

        temp = (*temp).next;
    }
    //for when there is no sufficient block of memory for requested memory, returns null to the user
    fprintf(stderr, "ERROR: Finished searching memory - not enough space for allocation\n");
    mallocErr = 1;
    return NULL;
}
/*void myfree(void* toFree, char* file, int line){
    
    freeErr = 0;
    metadata* temp = front;
    metadata* prev;
    
    //there has been no previous malloc call
    if(front == NULL){
        fprintf();
        freeErr = 1;
    }
    
    while(){
        
    }
    merge();
    
}*/

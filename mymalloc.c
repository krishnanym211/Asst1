#include "mymalloc.h"

metadata* front;
//allocation is returned, it is a void pointer that will be set to the first index of requested size
void* allocation;

//returns the last index of the block called on
int currIndex(metadata* block){
    metadata* temp = front;
    int data;
    //while the current block is not the block to count till
    while(temp != end){
        //count the structure size and block size, adding them
        data +=sizeof(metadata) + (*temp).size;
        temp = temp.next;
    }
    //return index of the first byte of block
    return data;
}

void* mymalloc(int size, char* file, int line){
    //if allocation size is equal to or less than 0, thats not valid
    if(size <= 0){
        fprintf(stderr,"");
        return NULL;
    }
    if(size + sizeof(metadata) >= 4096){
        fprintf(stderr,"");
        return NULL;
    }
    if(spaceUsed + size >= 4096){
        fprintf(stderr,"");
        return NULL;
    }
    //incase this is the first time malloc has been called
    if(firstMalloc == 0){
        front = (metadata*)myBlock;
        (*front).inUse = "y";
        (*front).size = size;
        allocation = &myBlock[(sizeof(metadata))];
        spaceUsed = sizeof(metadata)+size;
        firstMalloc = 1;
        mallocErr = 0;
        return allocation;
    }
    
    metadata* temp = front;
    metadata* prev;
    
    while(temp != 0){
        //incase current block exactly fits size of reuested amount
        if((*temp).inUse == "n" && (*temp).size == size){
            (*temp).inUse == "y";
            mallocErr = 0;
            allocation = &myBlock[currIndex(temp) + sizeof(metadata)];
            return allocation;
        }
        //incase first fit block is bigger than the size requested
        if((*temp).inUse == "n" && (*temp).size > (sizeof(metadata)+1+size)){
            //int value of index for the new block
            int allocData = currIndex(temp)+sizeof(metadata) +size;
            //create new block and fill structure
            metadata* new = (metadata*)(&myBlock[allocData]);
            (*new).next = (*temp).next;
            allocation = &myBlock[currIndex(temp) + sizeof(metadata)];
            (*temp).next = new;
            (*temp).inUse = "y";
            //subtract the size of the space requested and metadata from previous size to find the size of new block
            (*new).size =  ((*temp).size -size - sizeof(metadata));
            (*temp).size = size;
            //how do i knwo the size of the memory for the new block. calculate each time?
            (*new).inUse = "n";
            mallocErr = 0;
            return allocation;
        }
        if (*temp).next == NULL){
            break;
        }
        temp = (*temp).next;
    }
    //need a test case for when there is no sufficient block of memory for requested memory, returns null to the user
}
void myfree(void* pointer, char* file, int line){
    
}

#include <stdlib.h>

#define malloc( x ) mymalloc (x,__FILE__,__LINE__)
#define free( x ) myfree (x,__FILE__,__LINE__)


//function signatures
void* mymalloc(int size, char* file, int line);
void myfree(void* toFree, char* file, int line);

static char myBlock[4096];

typedef struct metadata{
    void* ptr;
    int size;
    char inUse;
    struct metadata* next;
}metadata;





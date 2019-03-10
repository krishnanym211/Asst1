all:
	gcc -c mymalloc.c && gcc -c memgrind.c && gcc mymalloc.o memgrind.o -o memgrind && ./memgrind
mymalloc:
	gcc mymalloc.c -o mymalloc

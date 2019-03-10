all:
	gcc -g -c mymalloc.c && gcc -g -c memgrind.c && gcc mymalloc.o memgrind.o -o memgrind
run:
	./memgrind
malloc:
	gcc -g mymalloc.c -o mymalloc
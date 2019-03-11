all:
	cp /dev/null errors.txt && gcc -g -c mymalloc.c && gcc -g -c memgrind.c && gcc mymalloc.o memgrind.o -o memgrind
run:
	./memgrind 2> errors.txt
malloc:
	gcc -g mymalloc.c -o mymalloc
clean:
	cp /dev/null errors.txt
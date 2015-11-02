all:
	$(info  ***** Building *****)
	gcc -c main.c
	gcc -c sorted-list.c
	ar rc libsl.a sorted-list.o
	gcc -o sl main.c libsl.a

clean:
	$(info  ***** Cleaning *****)
	rm -rf *.o
	rm -rf libsl.a


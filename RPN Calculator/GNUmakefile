all: main

main: main.c rpn.o stack.o
	gcc -Wall main.c rpn.o stack.o -o RPN

stack_test: stack_test.c stack.o 
	gcc -Wall stack_test.c stack.o -o stack_test

rpn_test: rpn_test.c rpn.o stack.o
	gcc -Wall rpn_test.c rpn.o stack.o -o rpn_test

stack.o: stack.c
	gcc -Wall -c stack.c

rpn.o: rpn.c
	gcc -Wall -c rpn.c

clean:
	rm -f *.o
	rm -f stack_test
	rm -f rpn_test

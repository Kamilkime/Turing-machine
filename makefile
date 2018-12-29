all:
	@gcc -pedantic -Wall src/*.c -o turing

clean: all
	@rm -f *.o

test: clean
	@./turing test/testMachine.tur
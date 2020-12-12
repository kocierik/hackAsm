main: main.o whiteSpace.o instruction.o
	gcc -o assembler main.o whiteSpace.o instruction.o

main.o: main.c whiteSpace.h
	gcc -c main.c

whiteSpace.o: whiteSpace.c whiteSpace.h
	gcc -c whiteSpace.c

instruction.o: instruction.c instruction.h
	gcc -c instruction.c

clean:
	rm *.o main
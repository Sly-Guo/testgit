CC = gcc
EXEC = program
CFLAGS = -wall -ansi -pedantic
OBJ = main_test.o newSleep.o 

${EXEC} : ${OBJ}
	$(CC) $(OBJ) -o ${EXEC}

main_test.o : newSleep.h
newSleep.o : newSleep.h

.PHONY : clean
clean :
	rm -f &{EXEC} $(OBJ)
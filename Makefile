CC = gcc
OUTPUT=program
FLAGS=-lGL -lGLU -lglut -lm
#all:
#		$(CC) *.c */*.c -lGL -lGLU -lglut -lm -o main

all:
		$(CC)  *.c $(FLAGS) -o $(OUTPUT)

run: all
	./$(OUTPUT)

clean:
		rm *.o -f

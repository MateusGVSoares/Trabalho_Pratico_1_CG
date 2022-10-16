CC = g++
OUTPUT=main
FLAGS=-lGL -lGLU -lglut -lm -lSOIL
#all:
#		$(CC) *.c */*.c -lGL -lGLU -lglut -lm -o main

all:
		$(CC) -g *.cpp */*.cpp */*/*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	./$(OUTPUT)

clean:
		rm *.o -f

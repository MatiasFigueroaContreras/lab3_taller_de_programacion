FLAGS = -g -Wall

all: clean test_Simplex run

test_Simplex: Simplex.o test_Simplex.cpp
	g++ $(FLAGS) -o test_Simplex Simplex.o test_Simplex.cpp

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

clean:
	rm -f test_Simplex *.o

run:
	./test_Simplex
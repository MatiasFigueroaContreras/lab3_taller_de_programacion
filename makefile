FLAGS = -O2 -g -Wall

all: clean test_Simplex test_MIPSolver run

main: MIPSolver.o Simplex.o main.cpp
	g++ $(FLAGS) -o main MIPSolver.o Simplex.o main.cpp

test_Simplex: Simplex.o test_Simplex.cpp
	g++ $(FLAGS) -o test_Simplex Simplex.o test_Simplex.cpp

test_MIPSolver: MIPSolver.o Simplex.o test_MIPSolver.cpp
	g++ $(FLAGS) -o test_MIPSolver MIPSolver.o Simplex.o test_MIPSolver.cpp

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

MIPSolver.o: MIPSolver.cpp MIPSolver.h
	g++ $(FLAGS) -c MIPSolver.cpp

clean:
	rm -f main test_Simplex test_MIPSolver *.o

run:
	./test_Simplex
	./test_MIPSolver
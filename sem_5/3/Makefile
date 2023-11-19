a.out: test.o matrix_creator.o func_knij.o solver_H.o 
	g++ -pthread test.o matrix_creator.o func_knij.o solver_H.o -o a.out -O3
test.o: test.cpp
	g++ -c test.cpp -O3
matrix_creator.o: matrix_creator.cpp
	g++ -c matrix_creator.cpp -O3
func_knij.o: func_knij.cpp
	g++ -c func_knij.cpp -O3
solver_H.o: solver_H.cpp
	g++ -pthread -c solver_H.cpp -O3


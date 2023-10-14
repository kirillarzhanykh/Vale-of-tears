a.out: test.o matrix_creator.o func_knij.o solver_H.o 
	g++ test.o matrix_creator.o func_knij.o solver_H.o -o a.out
test.o: test.cpp
	g++ -c test.cpp
matrix_creator.o: matrix_creator.cpp
	g++ -c matrix_creator.cpp
func_knij.o: func_knij.cpp
	g++ -c func_knij.cpp
solver_H.o: solver_H.cpp
	g++ -c solver_H.cpp


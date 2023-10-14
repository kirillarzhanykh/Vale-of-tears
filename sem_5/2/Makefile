a.out: test.o matrix_creator.o func_knij.o eigenvalues_QR.o 
	g++ test.o matrix_creator.o func_knij.o eigenvalues_QR.o -o a.out
test.o: test.cpp
	g++ -c test.cpp
matrix_creator.o: matrix_creator.cpp
	g++ -c matrix_creator.cpp
func_knij.o: func_knij.cpp
	g++ -c func_knij.cpp
eigenvalues_QR.o: eigenvalues_QR.cpp
	g++ -c eigenvalues_QR.cpp


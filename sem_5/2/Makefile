a.out: test.o matrix_creator.o func_knij.o eigenvalues_QR.o 
	g++ test.o matrix_creator.o func_knij.o eigenvalues_QR.o -o a.out -O3
test.o: test.cpp
	g++ -c test.cpp -O3
matrix_creator.o: matrix_creator.cpp
	g++ -c matrix_creator.cpp -O3
func_knij.o: func_knij.cpp
	g++ -c func_knij.cpp -O3
eigenvalues_QR.o: eigenvalues_QR.cpp
	g++ -c eigenvalues_QR.cpp -O3


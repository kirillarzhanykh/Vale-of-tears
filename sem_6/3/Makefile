a.out: main.o solver_H.o eigenvalues_QR.o
	g++ main.o solver_H.o eigenvalues_QR.o -o a.out -O3
main.o: main.cpp
	g++ -c main.cpp -O3
solver_H.o: solver_H.cpp
	g++ -c solver_H.cpp -O3
eigenvalues_QR.o: eigenvalues_QR.cpp
	g++ -c eigenvalues_QR.cpp -O3

a.out: main.o eigenvalues_QR.o
	g++ main.o eigenvalues_QR.o -o a.out -O3
main.o: main.cpp
	g++ -c main.cpp -O3
eigenvalues_QR.o: eigenvalues_QR.cpp
	g++ -c eigenvalues_QR.cpp -O3

#include <iostream>
#include <cmath>
#include <fstream>

const double PI = 3.14159265358979323846;


double ex2(double x);

int SolveFiniteDifference(int N,double* A, double* B, double* u,double* x,double h,double* adjoint);
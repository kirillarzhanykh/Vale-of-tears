
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

void system(const double *x, double *dxdt, double t, double alpha);

void Runge_Kutta4(int n, double *x1, double *x2, double *p1, double *p2,double x1_0, double x2_0, double p1_0, double p2_0, double alpha, double h, double *u);

void Shooter_cond(double a, double b, int n, double* x1, double* x2, double* p1, double* p2, double alpha, double h, double& F1, double& F2, double *u);

void solve_ab(int n, double alpha, double* ab, double* x1, double* x2, double* p1, double* p2, double h, double *u);


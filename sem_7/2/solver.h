
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double diff_system(int i, double t, double x1, double x2, double p1, double p2, double alpha);

void Runge_Kutta(int n, double* x1, double* x2, double* p1, double* p2, double x1_0, double x2_0, double p1_0, double p2_0, double alpha, double h);

void Runge_Kutta4_Adaptive(int n, double* x1, double* x2, double* p1, double* p2,
                           double x1_0, double x2_0, double p1_0, double p2_0,
                      double alpha, double& h, double t_end, double tol);

void system(const double *x, double *dxdt, double t, double alpha);

void Runge_Kutta4(int n, double *x1, double *x2, double *p1, double *p2,double x1_0, double x2_0, double p1_0, double p2_0, double alpha, double h);
void Runge_Kutta5(int n, double *x1, double *x2, double *p1, double *p2,
                  double x1_0, double x2_0, double p1_0, double p2_0,
                  double alpha, double h);
void Shouter_cond(double a, double b, int n, double* x1, double* x2, double* p1, double* p2, double alpha, double h, double& F1, double& F2);

void Secant(double* ab, double W[2][2], double F_prev[2], int n, double* x1, double* x2, double* p1, double* p2, double alpha, double h);

void find_ab(int n, double alpha, double* ab, double* x1, double* x2, double* p1, double* p2, double h);

void solve_ab(int n, double alpha, double* ab, double* x1, double* x2, double* p1, double* p2, double h);


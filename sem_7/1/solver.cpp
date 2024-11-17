#include "solver.h"
#define alpha 10

double none(double x){
    return 0;
}

double k_func(double x){
    if(x > 1/2) return 2;
    return 1;
}



// Функция правой части системы ОДУ для неоднородного уравнения
void ODESystemNonHomogeneous(double x, const double y[], double dydx[]) {
    // y[0] = u
    // y[1] = u'
    dydx[0] = y[1];
    dydx[1] = (alpha*y[0] - std::exp(x * x))/k_func(x);
}



// Метод Рунге-Кутты второго порядка для системы ОДУ
void RungeKutta2( double (*func)(double), double h, const double y0[], double x_vals[], double y_vals[], int N_points, int dim) {

    // Инициализация массивов
    double *y = new double[dim];
    double *k1 = new double[dim];
    double *k2 = new double[dim];

    x_vals[0] = 0;
    for (int j = 0; j < dim; ++j) {
        y_vals[0 * dim + j] = y0[j];
    }

    for (int i = 0; i < N_points - 1; ++i) {
        
        for (int j = 0; j < dim; ++j) {
            y[j] = y_vals[i * dim + j];
        }

        //ODE(x_vals[i], y, k1);
        k1[0] = y[1];
        k1[1] = (alpha*y[0] - func(x_vals[i]))/k_func(x_vals[i]);

    
        for (int j = 0; j < dim; ++j) {
            y[j] += h * k1[j];
        }
        //ODE(x_vals[i] + h, y, k2);
        k1[0] = y[1];
        k1[1] = (alpha*y[0] - func(x_vals[i]))/k_func(x_vals[i]);

        for (int j = 0; j < dim; ++j) {
            y_vals[(i + 1) * dim + j] = y_vals[i * dim + j] + h * 0.5 * (k1[j] + k2[j]);
            y[j] = y_vals[i * dim + j];
        }
    }

    // Освобождение памяти
    delete[] y;
    delete[] k1;
    delete[] k2;
}



int ShooterMethod(double (*func)(double),int N_points,int dim,double h, double* y_vals, double* x_vals, double* u_vals,double* phi1_full,double* phi2_full,double* psi_full){
    // Нарезка сетки по x
    for(int i =0; i< N_points; i++){
        x_vals[i] = i * h;
    }
    
    // Решение для phi1 (фундаментальное решение 1)
    double y0_phi1[2] = {1.0, 0.0}; // u(0)=1, u'(0)=0 
    RungeKutta2(none, h, y0_phi1, x_vals, y_vals, N_points, dim);
    

    // Сохраняем значения phi1 и phi1'
    double phi1_0 = y_vals[0];
    double phi1_1 = y_vals[(N_points - 1) * dim + 0];
    
    // Сохраняем решение phi1 для дальнейшего использования
    for (int i = 0; i < N_points; ++i) {
        for (int j = 0; j < dim; ++j) {
            phi1_full[i * dim + j] = y_vals[i * dim + j];
        }
    }

    // Решение для phi2 (фундаментальное решение 2)
    double y0_phi2[2] = {0.0, 1.0}; // u(0)=0, u'(0)=1
    RungeKutta2(none, h, y0_phi2, x_vals, y_vals, N_points, dim);

    // Сохраняем значения phi2 и phi2'
    double phi2_0 = y_vals[0];      // y[0][0]
    double phi2_1 = y_vals[(N_points - 1) * dim + 0]; // y[N][0]

    // Сохраняем решение phi2 для дальнейшего использования
    for (int i = 0; i < N_points; ++i) {
        for (int j = 0; j < dim; ++j) {
            phi2_full[i * dim + j] = y_vals[i * dim + j];
        }
    }

    // Решение для psi (частное решение)
    double y0_psi[2] = {0.0, 0.0}; // u(0)=0, u'(0)=0, u''(0)=0, u'''(0)=0
    RungeKutta2(func, h, y0_psi, x_vals, y_vals, N_points, dim);

    // Сохраняем значения psi и psi'
    double psi_0 = y_vals[0];      // y[0][0]
    double psi_1 = y_vals[(N_points - 1) * dim + 0]; // y[N][0]

    // Сохраняем решение psi для дальнейшего использования

    for (int i = 0; i < N_points; ++i) {
        for (int j = 0; j < dim; ++j) {
            psi_full[i * dim + j] = y_vals[i * dim + j];
        }
    }
    
    

    // Составляем систему линейных уравнений для нахождения C1 и C2
    // C1 * phi1(0) + C2 * phi2(0) + psi(0) = 1
    // C1 * phi1(1) + C2 * phi2(1) + psi(1) = 0

    double b1 = 1.0 - psi_0;
    double b2 = 0.0 - psi_1;

    // Матрица коэффициентов
    double a11 = phi1_0;
    double a12 = phi2_0;
    double a21 = phi1_1;
    double a22 = phi2_1;

    // Вычисляем определитель матрицы
    double det = a11 * a22 - a12 * a21;

    if (std::abs(det) < 1e-16) {
        return -1;
    }

    // Решаем систему методом Крамера
    double C1 = (b1 * a22 - b2 * a12) / det;
    double C2 = (a11 * b2 - a21 * b1) / det;

    
    for (int i = 0; i < N_points; ++i) {
        u_vals[i] = C1 * phi1_full[i * dim + 0] + C2 * phi2_full[i * dim + 0] + psi_full[i * dim + 0];
    }


    
    return 1;
}
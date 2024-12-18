
#include "solver.h"

// Функция системы уравнений
void system(const double *x, double *dxdt, double t, double alpha) {
    //x[1] = x2  x[0] = x1 x[3] = p2 x[2] = p1
    dxdt[0] = x[1]; 
    dxdt[1] = x[3] + x[0] * std::exp(-alpha * x[0]); 
    dxdt[2] =  x[3] * std::exp(-alpha * x[0]) * (alpha * x[0] - 1.0);
    dxdt[3] = -x[2]; 
}




// Метод Рунге-Кутты 4-го порядка
void Runge_Kutta4(int n, double *x1, double *x2, double *p1, double *p2,
                 double x1_0, double x2_0, double p1_0, double p2_0,
                 double alpha, double h, double *u) {
    double k1[4], k2[4], k3[4], k4[4];
    double state[4], temp_state[4];

    x1[0] = x1_0;
    x2[0] = x2_0;
    p1[0] = p1_0;
    p2[0] = p2_0;

    double t_i = 0.0;

    for (int i = 1; i < n ; i++) {
        state[0] = x1[i - 1];
        state[1] = x2[i - 1];
        state[2] = p1[i - 1];
        state[3] = p2[i - 1];

        
        system(state, k1, t_i, alpha);

       
        for (int j = 0; j < 4; ++j) {
            temp_state[j] = state[j] + k1[j] * h / 2.0;
        }
        system(temp_state, k2, t_i + h / 2.0, alpha);

       
        for (int j = 0; j < 4; ++j) {
            temp_state[j] = state[j] + k2[j] * h / 2.0;
        }
        system(temp_state, k3, t_i + h / 2.0, alpha);

        // Вычисление k4
        for (int j = 0; j < 4; ++j) {
            temp_state[j] = state[j] + k3[j] * h;
        }
        system(temp_state, k4, t_i + h, alpha);

        // Обновление переменных
        x1[i] = x1[i - 1] + h * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]) / 6.0;
        x2[i] = x2[i - 1] + h * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]) / 6.0;
        p1[i] = p1[i - 1] + h * (k1[2] + 2.0 * k2[2] + 2.0 * k3[2] + k4[2]) / 6.0;
        p2[i] = p2[i - 1] + h * (k1[3] + 2.0 * k2[3] + 2.0 * k3[3] + k4[3]) / 6.0;

        t_i += h;

        u[i] = p1[i] * std::exp(-alpha * x1[i]) * (alpha * x1[i] - 1.0) - x1[i] * std::exp(-alpha * x1[i]);
    }
}


void Shooter_cond(double a, double b, int n, double* x1, double* x2, double* p1, double* p2, double alpha, double h, double& F1, double& F2, double *u) {
    Runge_Kutta4(n, x1, x2, p1, p2, 0.0, 0.0 , a, b, alpha, h, u);
    F1 = x1[n - 1] - std::sinh(1);
    F2 = x2[n - 1] - std::exp(1); 
    
}



double norma_fedor(int n, double *F, double *fedot_temp) {
    double res = 0.0;
    for (int i = 0; i < n; i++) {

        res += (F[i] * F[i]) / fedot_temp[i];
    }
    return sqrt(res);
}


void solve_ab(int n, double alpha, double* ab, double* x1, double* x2, double* p1, double* p2, double h, double* u) {
    
    const double eps = 1e-15;   // Точность остановки
    const double delta = 1e-10; // Шаг для конечных разностей
    double W[2][2];             // Матрица Якобиана
    double F[2];                // Значения функций в текущих точках
    double F_temp_plus[2], F_temp_minus[2]; // Временные значения для центральных разностей
    double delta_ab[2];         // Приращения для ab
    double fedot_temp[2];            // Массив для нормировки по Федоренко

    ab[0] = 0;
    ab[1] = 2; 

    // Вычисляем начальные значения функций
    Shooter_cond(ab[0], ab[1], n, x1, x2, p1, p2, alpha, h, F[0], F[1], u);
    
    double norm_fedor = norma_fedor(2, F, fedot_temp);
    
    //std::cout<<norm_fedor<<std::endl;
    
    double a_orig = ab[0];
    double b_orig = ab[1];

    // Вычисляем Якобиан по a
    ab[0] = a_orig + delta;
    Shooter_cond(ab[0], b_orig, n, x1, x2, p1, p2, alpha, h, F_temp_plus[0], F_temp_plus[1], u);

    ab[0] = a_orig - delta;
    Shooter_cond(ab[0], b_orig, n, x1, x2, p1, p2, alpha, h, F_temp_minus[0], F_temp_minus[1], u);

    W[0][0] = (F_temp_plus[0] - F_temp_minus[0]) / (2.0 * delta);
    W[1][0] = (F_temp_plus[1] - F_temp_minus[1]) / (2.0 * delta);

    ab[0] = a_orig; // Возвращаемся к исходному a

    // Вычисляем Якобиан по b
    ab[1] = b_orig + delta;
    Shooter_cond(a_orig, ab[1], n, x1, x2, p1, p2, alpha, h, F_temp_plus[0], F_temp_plus[1], u);

    ab[1] = b_orig - delta;
    Shooter_cond(a_orig, ab[1], n, x1, x2, p1, p2, alpha, h, F_temp_minus[0], F_temp_minus[1], u);

    W[0][1] = (F_temp_plus[0] - F_temp_minus[0]) / (2.0 * delta);
    W[1][1] = (F_temp_plus[1] - F_temp_minus[1]) / (2.0 * delta);

    ab[1] = b_orig; // Возвращаемся к исходному b

    // Итерационный процесс метода Ньютона
    while (true) {
        // Вычисляем детерминант Якобиана
        double det = W[0][0] * W[1][1] - W[0][1] * W[1][0];
        if (fabs(det) < 1e-32) {
            std::cerr << "Детерминант Якобиана равен нулю, не можем продолжить." << std::endl;
            break;
        }
        
        // Вычисляем приращения delta_ab
        delta_ab[0] = (-F[0] * W[1][1] + F[1] * W[0][1]) / det;
        delta_ab[1] = (W[0][0] * -F[1] + W[1][0] * F[0]) / det;
        
        // Обновляем значения ab
        ab[0] += delta_ab[0];
        ab[1] += delta_ab[1];
        
        // Сохраняем старое F
        double F_old[2] = {F[0], F[1]};
        

        Shooter_cond(ab[0], ab[1], n, x1, x2, p1, p2, alpha, h, F[0], F[1], u);
        
        
        for (int i = 0; i < 2; i++) {
            fedot_temp[i] = 0.0;
            for (int j = 0; j < 2; j++) {
                fedot_temp[i] += W[i][j] * W[i][j];
            }
        }
        
        // Вычисляем норму по Федоренко
        norm_fedor = norma_fedor(2, F, fedot_temp);
        //std::cout<<norm_fedor<<std::endl;
        // Проверяем условие остановки по норме Федоренко
        if (norm_fedor < eps) {
            //std::cout<<norm_fedor<<std::endl;
            break;
        }
        
        // Обновление Якобиана по Федоренко
        double y[2] = {F[0] - F_old[0], F[1] - F_old[1]};
        double s[2] = {delta_ab[0], delta_ab[1]};
        double s_dot_s = s[0] * s[0] + s[1] * s[1];
        
        for (int i = 0; i < 2; ++i) {
            double diff = y[i] - (W[i][0] * s[0] + W[i][1] * s[1]);
            for (int j = 0; j < 2; ++j) {
                W[i][j] += (diff * s[j]) / s_dot_s;
            }
        }
    }
}


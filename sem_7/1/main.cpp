/*

Задача:
- (k u')' + a * u = ex2,
u(0) = 1, u(1) = 0, a = 1 , 10
k = { 1  при x < 1/2; 2  при x > 1/2 }
 
*/



#include <cstdlib>        // Для std::stod
#include <ctime>          // Для измерения времени работы алгоритма
#include <fstream> 
#include <iomanip>       // Для сохранения результатов в файл
#include "solver.h"

#define alpha 1


using namespace std;

double ex2(double x) {
    return exp(x * x);
}

double testfunc(double x) {
    return 2*k_func(x) + alpha*(1-x*x);
}

int main(int argc, char* argv[]) {
    // Проверяем, что передано два аргумента: шаг h и имя выходного файла
    if (argc < 3) {
        cout << "Недостаточно аргументов командной строки." << endl;
        cout << "Использование: " << argv[0] << " <h> <output_file>" << endl;
        return 1;
    }

    // Преобразуем переданный аргумент h в число с плавающей запятой
    double h = stod(argv[1]);

    // Имя файла для сохранения решения
    const char* output_file = argv[2];
    

    // Определяем количество узлов на сетке
    int n = static_cast<int>(1.0 / h) + 1;
    int dim = 2;
    
    // Вывод аргументов
    cout << "Полученные аргументы: h = " << h << ", n = " << n << endl;

    // Выделяем память под матрицы и векторы
    double *x_vals = new double[n];
    double *y_vals = new double[n * dim];
    double *u_vals = new double[n];
    double *phi1_full = new double[n* dim];
    double *phi2_full = new double[n* dim];
    double *psi_full = new double[n* dim];
    
    
    clock_t t;
    t = clock();
            
    //int res = ShooterMethod(ex2,n, dim, h, y_vals, x_vals, u_vals,phi1_full,phi2_full,psi_full);
    int res = ShooterMethod(testfunc,n, dim, h, y_vals, x_vals, u_vals,phi1_full,phi2_full,psi_full);
        
    // Если не удалось найти решение (обратную матрицу), выводим сообщение
    if (res == -1) {
        cout << "Не существует обратной матрицы." << endl;
    } else {
        // Вычисляем время выполнения
        t = clock() - t;
        double elapsed_time = t * 1.0 / CLOCKS_PER_SEC;
        cout << "Время работы алгоритма в секундах: " << elapsed_time << endl;

        // Сохраняем решение в файл
        ofstream outfile(output_file);
        for (int i = 0; i < n; ++i) {
            //outfile << x_vals[i] << " " << u_vals[i] << endl;
            outfile <<std::setprecision(19)<< x_vals[i] << " " << u_vals[i]<<" "<< 1 - x_vals[i]*x_vals[i] << endl;
        }
        outfile.close();
        cout << "Решение сохранено в файл " << output_file << endl;

        // Добавим запись в файл с таблицей времени выполнения
        ofstream timing_file("timing_results.txt", ios::app);
        timing_file << "h = " << h << ", Время выполнения: " << elapsed_time << " секунд" << endl;
        timing_file.close();
    }
        

    // Освобождаем память
    delete[] x_vals;
    delete[] y_vals;
    delete[] u_vals;
    delete[] phi1_full;
    delete[] phi2_full;
    delete[] psi_full;

    return 0;
}



#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include "solver.h"

// Главная функция
int main(int argc, char* argv[]) {
    // Проверяем наличие аргументов командной строки
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " h" << std::endl;
        return 1;
    }

    // Читаем значение h из аргументов командной строки
    //double h = std::stod(argv[1]);

    double T = 1.0;
    int n = 100000;
    double h = T/(n-1);
    //int n = T / h;
    //n = 10000;
    //double alpha_values[] = { 0.0, -0.1, 0.1, -1.0, 1.0};
    double alpha_values[] = { 0.0, 0.01, 0.5, 5.0, 10.5};
    int num_alpha = sizeof(alpha_values) / sizeof(alpha_values[0]);

    double* x1 = new double[n];
    double* x2 = new double[n];
    double* p1 = new double[n];
    double* p2 = new double[n];

    // Создаем папку для решений, если она не существует
    system("mkdir -p solutions");

    for (int idx = 0; idx < num_alpha; ++idx) {
        double alpha = alpha_values[idx];
        //std::cout << "Решение для alpha = " << alpha << std::endl;

        double ab[2]; // a и b
        solve_ab(n, alpha, ab, x1, x2, p1, p2, h);

        // Запись данных в текстовый файл
        std::ostringstream filename_stream;
        filename_stream << "solutions/alpha" << idx << "_h" << h << ".txt";
        std::cout<< std::setprecision(10);
        std::cout << "alpha=" << alpha
                  << " x1(0)=" << x1[0]
                  << " x2(0)=" << x2[0]
                  << " p1(0)=" << p1[0]
                  << " p2(0)=" << p2[0]
                  << std::endl;
        std::cout << "Решение для alpha = " << alpha << " и h = " << h << " записано в файл " << filename_stream.str() << std::endl;
        std::string filename = filename_stream.str();
        std::ofstream outfile(filename);
        if (outfile.is_open()) {
            // Записываем заголовки
            outfile << "# alpha = " << alpha << std::endl;
            outfile << "# a = " << ab[0] << ", b = " << ab[1] << std::endl;
            outfile << "# t x1 x2 p1 p2" << std::endl;
            outfile << std::scientific << std::setprecision(10);
            for (int i = 0; i < n; ++i) {
                double t = i * h;
                outfile << t << " " << x1[i] << " " << x2[i] << " " << p1[i] << " " << p2[i] << std::endl;
            }
            outfile.close();
        }
        else {
            std::cerr << "Не удалось открыть файл " << filename << " для записи." << std::endl;
        }
    }

    delete[] x1;
    delete[] x2;
    delete[] p1;
    delete[] p2;

    return 0;
}

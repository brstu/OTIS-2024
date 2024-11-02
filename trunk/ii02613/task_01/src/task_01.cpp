#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Константы
const double a = 1.0;
const double b = 0.5;
const double c = 0.1;
const double d = 0.9;

// Параметры симуляции
const int n = 10;  // Колличество временных шагов

// Линейная модель
std::vector<double> linear_model(double initial_temp, int n, double warm) {
    std::vector<double> y(n);
    y[0] = initial_temp;
    for (int tau = 1; tau < n; ++tau) {
        y[tau] = a * y[tau-1] + b * warm;
    }
    return y;
}

// Нелинейная модель
std::vector<double> nonlinear_model(double initial_temp, int n, double warm) {
    std::vector<double> y(n);
    y[0] = initial_temp;
    for (int tau = 1; tau < n; ++tau) {
        y[tau] = a * y[tau-1] - b * pow(y[tau-1], 2) + c * warm + d * sin(warm);
    }
    return y;
}

int main() {
    double initial_temp, warm;

    std::cout << "Введите начальную температуру: ";
    std::cin >> initial_temp;

    std::cout << "Введите значение теплоты: ";
    std::cin >> warm;

    // Запуск семуляции
    std::vector<double> y_linear = linear_model(initial_temp, n, warm);
    std::vector<double> y_nonlinear = nonlinear_model(initial_temp, n, warm);

    // Вывод результатов в терминал
    std::cout << std::setw(10) << "Time" 
              << std::setw(20) << "Linear Model" 
              << std::setw(20) << "Nonlinear Model" 
              << std::setw(20) << "Input" << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout << std::fixed << std::setprecision(6)
                  << std::setw(10) << i
                  << std::setw(20) << y_linear[i]
                  << std::setw(20) << y_nonlinear[i]
                  << std::setw(20) << warm << std::endl;
    }

    return 0;
}
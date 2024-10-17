#include <iostream>
#include <cmath>
#include <iomanip>

// Линейная модель
double linearModel(double a, double b, double y_linear, double u) {
    return a * y_linear + b * u;
}

// Нелинейная модель
double nonlinearModel(double a, double b, double c, double d, double y_nonlinear, double y_nonlinear_prev, double u_prev, double u) {
    return a * y_nonlinear - b * std::pow(y_nonlinear_prev, 2) + c * u + d * std::sin(u_prev);
}

int main(int argc, char* argv[]) {
    // Константы
    double a = 0.5;
    double b = 0.001;
    double c = 0.2;
    double d = 0.5;
    double y0; // начальная температура
    std::cout << "input temperature: ";
    std::cin >> y0;
    double u0; // начальное тепло
    std::cout << "input warm: ";
    std::cin >> u0;
    int n = 40; //число повторений

    // Начальные условия
    double y_linear = y0;
    double y_nonlinear = y0;
    double u = u0;
    double u_prev = u0;
    double y_linear_new;
    double y_nonlinear_new;
    double y_nonlinear_prev = y0;

    std::cout << std::setw(30) << "Linear model" << std::setw(30) << "Nonlinear model" << std::endl;

    // Симуляция на несколько шагов
    for (int t = 0; t < n; t++) {
        // Линейная модель
        y_linear_new = linearModel(a, b, y_linear, u);
        std::cout << "Time: " << t << std::setw(20) << y_linear;
        y_linear = y_linear_new;

        // Нелинейная модель
        y_nonlinear_new = nonlinearModel(a, b, c, d, y_nonlinear, y_nonlinear_prev, u, u_prev);
        std::cout << std::setw(30) << y_nonlinear << std::endl;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_new;
    }
    system("pause");
    return 0;
}

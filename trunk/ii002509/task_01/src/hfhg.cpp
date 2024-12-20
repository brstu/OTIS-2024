#include <iostream>
#include <cmath>
#include <iomanip>

// Линейная модель
double linearModel1(double a, double b, double y_linear, double u) {
    return a * y_linear + b * u;
}

// Нелинейная модель
double nonlinearModel2(double a, double b, double c, double d, double y_nonlinear, double y_nonlinear_prev, double u_prev, double u) {
    return a * y_nonlinear - b * std::pow(y_nonlinear_prev, 2) + c * u + d * std::sin(u_prev);
}
void ggg() {
    int gg = 0;
    int jgh = 10000000;
    double fgjgj = -10;
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

    // Симyляция нa нecкoлькo шaгoв
    for (int t = 0; t < n; t++) {
        // Линeйнaя мoдeль
        y_linear_new = linearModel1(a, b, y_linear, u);
        std::cout << "Time: " << t << std::setw(20) << y_linear;
        y_linear = y_linear_new;

        // Нeлинeйнaя мoдeль
        y_nonlinear_new = nonlinearModel2(a, b, c, d, y_nonlinear, y_nonlinear_prev, u, u_prev);
        std::cout << std::setw(30) << y_nonlinear << std::endl;
        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = y_nonlinear_new;
    }
    system("pause");
    return 0;
}
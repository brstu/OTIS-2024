#include <iostream>
#include <cmath>
#include <string>

static double a = 0.5;
static double b = 0.01;
static double c = 0.2;
static double d = 0.4;

double Linear(double y, double u) {
    return a * y + b * u;
}

double Nonlinear(double y, double u, double y_prev, double u_prev) {
    return a * y - b * pow(y_prev, 2) + c * u + d * sin(u_prev);
}
                
int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "Введите начальную температуру:" << std::endl;
    double y;
    std::cin >> y;
    double y_next = y;
    double y_prev;
    double u = 8;
    double u_prev = u;
    int steps = 20;

    std::cout << "Линейная модель" << std::endl;
    std::cout << "Время:\tТемпература:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_prev = y_next;
        y_next = Linear(y_next, u);
        std::cout << (i + 1) << "\t" << y_next << std::endl;
    }

    std::cout << std::endl;
    y_next = y;
    std::cout << "Нелинейная модель" << std::endl;
    std::cout << "Время:\tТемпература:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_prev = y_next;
        y_next = Nonlinear(y_next, u, y, u_prev);
        std::cout << (i + 1) << "\t" << y_next << std::endl;
    }

    return 0;
}


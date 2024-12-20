#include <iostream>
#include <cmath>

// Константы
const double a = 0.5;  // Пример значения
const double b = 0.1;  // Пример значения
const double c = 0.05; // Пример значения
const double d = 0.01; // Пример значения

const int time_steps = 100; // Количество шагов по времени

void simulate_linear_model(double y[], double u[]) {
    for (int t = 0; t < time_steps; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
        std::cout << "Linear Model at time " << t << ": " << y[t + 1] << std::endl;
    }
}

void simulate_nonlinear_model(double y[], double u[]) {
    for (int t = 1; t < time_steps; ++t) {
        y[t + 1] = a * y[t] - b * y[t - 1] * y[t - 1] + c * y[t] + d * std::sin(u[t - 1]);
        std::cout << "Nonlinear Model at time " << t << ": " << y[t + 1] << std::endl;
    }
}

int main() {
    double y[time_steps + 1] = { 0 }; // Инициализация массива температур
    double u[time_steps] = { 0 };   // Инициализация массива теплового воздействия

    // Пример заполнения массива u значениями теплового воздействия
    for (int t = 0; t < time_steps; ++t) {
        u[t] = 1.0; // Например, постоянное воздействие
    }

    // Симуляция линейной модели
    simulate_linear_model(y, u);

    // Симуляция нелинейной модели
    simulate_nonlinear_model(y, u);

    return 0;
}

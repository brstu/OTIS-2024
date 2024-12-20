#include <iostream>
#include <cmath>
#include <iomanip>

// Линейная модель
double linearModel(double coeff_a, double coeff_b, double temp_linear, double heat_input) {
    return coeff_a * temp_linear + coeff_b * heat_input;
}

// Нелинейная модель
double nonlinearModel(double coeff_a, double coeff_b, double coeff_c, double coeff_d,
    double temp_nonlinear, double prev_temp_nonlinear,
    double prev_heat_input, double current_heat_input) {
    return coeff_a * temp_nonlinear - coeff_b * std::pow(prev_temp_nonlinear, 2)
        + coeff_c * current_heat_input + coeff_d * std::sin(prev_heat_input);
}

// Функция для ввода начальных данных
void inputInitialConditions(double& initial_temp, double& initial_heat) {
    std::cout << "Input initial temperature: ";
    std::cin >> initial_temp;
    std::cout << "Input initial heat input: ";
    std::cin >> initial_heat;
}

// Функция для выполнения симуляции
void runSimulation(int steps, double coeff_a, double coeff_b, double coeff_c, double coeff_d,
    double initial_temp, double initial_heat) {
    // Начальные условия
    double temp_linear = initial_temp;
    double temp_nonlinear = initial_temp;
    double current_heat_input = initial_heat;
    double prev_heat_input = initial_heat;
    double new_temp_linear;
    double new_temp_nonlinear;
    double prev_temp_nonlinear = initial_temp;

    std::cout << std::setw(30) << "Linear Model" << std::setw(30) << "Nonlinear Model" << std::endl;

    // Симуляция на несколько шагов
    for (int time_step = 0; time_step < steps; time_step++) {
        // Линейная модель
        new_temp_linear = linearModel(coeff_a, coeff_b, temp_linear, current_heat_input);
        std::cout << "Time Step: " << time_step << std::setw(20) << temp_linear;
        temp_linear = new_temp_linear;

        // Нелинейная модель
        new_temp_nonlinear = nonlinearModel(coeff_a, coeff_b, coeff_c, coeff_d,
            temp_nonlinear, prev_temp_nonlinear,
            prev_heat_input, current_heat_input);
        std::cout << std::setw(30) << temp_nonlinear << std::endl;
        prev_temp_nonlinear = temp_nonlinear;
        temp_nonlinear = new_temp_nonlinear;
    }
}

// Основная функция
int main(int argc, char* argv[]) {
    // Константы
    const double coeff_a = 0.5;
    const double coeff_b = 0.001;
    const double coeff_c = 0.2;
    const double coeff_d = 0.5;
    const int steps = 40; // число повторений

    double initial_temp; // начальная температура
    double initial_heat; // начальное тепло

    // Ввод данных
    inputInitialConditions(initial_temp, initial_heat);

    // Запуск симуляции
    runSimulation(steps, coeff_a, coeff_b, coeff_c, coeff_d, initial_temp, initial_heat);

    system("pause");
    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double A = 0.5;
const double B = 0.6;
const double C = 0.6;
const double D = 0.6;
const double K = 0.8;
const double T0 = 1.1;
const double TD = 1.0;
const double T = 1.1;
const double TARGET_VALUE = 20.0;

// Предвычисленные коэффициенты
const double q0 = K * (1 + (TD / T0));
const double q1 = -K * (1 + 2 * (TD / T0) - (T0 / T));
const double q2 = K * (TD / T0);

void simulateNonlinearModel() {
    const double initialY = 2.0;
    std::vector<double> outputs = { initialY, initialY }; // Вектор для хранения значений переменной y
    double controlSignal = 1.0; // Начальное значение управляющей переменной u
    std::vector<double> errors = { TARGET_VALUE - initialY, TARGET_VALUE - initialY }; // Вектор для хранения значений разности TARGET_VALUE - y
    std::vector<double> controlSignals = { controlSignal, controlSignal }; // Вектор для хранения значений предыдущей управляющей переменной u

    // Моделирование
    while (std::abs(TARGET_VALUE - outputs.back()) > 0.01) { // Цикл выполняется, пока разница между TARGET_VALUE и последним значением y больше 0.01
        errors.push_back(TARGET_VALUE - outputs.back()); // Добавление текущей разности в вектор errors
        controlSignal = controlSignals.back() + q0 * errors.back() + q1 * errors[errors.size() - 2];

        // Проверка на наличие достаточного количества элементов в errors для использования q2
        if (errors.size() >= 3) {
            controlSignal += q2 * errors[errors.size() - 3];
        }

        // Вычисление нового значения переменной y
        outputs.push_back(A * outputs.back() - B * outputs[outputs.size() - 2] + C * controlSignal + D * std::sin(controlSignals.back()));
        controlSignals.push_back(controlSignal); // Добавление нового значения управляющей переменной u в вектор controlSignals
    }

    // Вывод результатов моделирования
    for (std::size_t i = 0; i < outputs.size(); i++) {
        std::cout << i + 1 << ") y[" << i << "] = " << outputs[i] << std::setw(15);
        std::cout << "e[" << i << "] = " << errors[i] << std::setw(15);
        std::cout << "u_pr[" << i << "] = " << controlSignals[i] << std::endl; // Вывод значений y, e и u_pr на каждой итерации цикла
    }
}

int main() {
    simulateNonlinearModel(); // Вызов функции моделирования
    return 0;
}
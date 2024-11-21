#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Коэффициенты системы
const double a = 0.9;
const double b = 0.3;
const double c = 0.4;
const double d = 0.1;

// Параметры системы
const double trans_coeff_K = 0.9;
const double time0 = 0.5, timeC = 1.0, timeD = 0.5;
const double req_output = 20;

// Параметры регулятора
const double par1 = trans_coeff_K * (1 + (timeD / time0));
const double par2 = -trans_coeff_K * (1 + 2 * (timeD / time0) - (time0 / timeC));
const double par3 = trans_coeff_K * (timeD / time0);

void RunNonlinearModel() {
    // Начальные значения
    const short int initial_value = 2;
    std::vector<double> model_output = { initial_value, initial_value }; // Вектор результатов модели
    std::vector<double> errors = { req_output - initial_value, req_output - initial_value }; // Вектор ошибок
    double control_signal = 1;
    std::vector<double> control_signals = { control_signal, control_signal }; // Вектор контрольных сигналов

    // Основной цикл моделирования
    while (std::abs(req_output - model_output.back()) > 0.01) {
        // Обновление ошибки
        errors.push_back(req_output - model_output.back());

        // Вычисление контрольного сигнала
        control_signal += par1 * errors.back() + par2 * errors[errors.size() - 2] + par3 * errors[errors.size() - 3];
        control_signals.push_back(control_signal);

        // Обновление результата модели
        model_output.push_back(a * model_output.back() - b * model_output[model_output.size() - 2] + c * control_signal + d * std::sin(control_signals.back()));
    }

    // Вывод результатов
    std::cout << std::right << std::setw(10) << "Итерация"
        << std::setw(10) << "Вывод"
        << std::setw(13) << "Ошибка"
        << std::setw(13) << "Контроль" << std::endl;

    for (size_t i = 0; i < model_output.size(); ++i) {
        std::cout << std::right << std::setw(10) << i + 1
            << std::setw(10) << model_output[i]
            << std::setw(13) << errors[i]
            << std::setw(13) << control_signals[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    RunNonlinearModel();
    return 0;
}
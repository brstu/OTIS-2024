#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <locale>

// Константы модели
constexpr double kAlpha = 0.9;
constexpr double kBeta = 0.3;
constexpr double kGamma = 0.4;
constexpr double kDelta = 0.1;

// Параметры системы управления
constexpr double kCoeffK = 0.9;
constexpr double kTime0 = 0.5;
constexpr double kTimeC = 1.0;
constexpr double kTimeD = 0.5;
constexpr double kTargetOutput = 20.0;

// Вычисленные параметры регулятора
constexpr double kParam1 = kCoeffK * (1.0 + (kTimeD / kTime0));
constexpr double kParam2 = -kCoeffK * (1.0 + 2.0 * (kTimeD / kTime0) - (kTime0 / kTimeC));
constexpr double kParam3 = kCoeffK * (kTimeD / kTime0);

void SimulateControlSystem() {
    // Начальные условия
    constexpr int kInitialValue = 2;
    std::vector<double> systemOutputs = {kInitialValue, kInitialValue};
    std::vector<double> errors = {kTargetOutput - kInitialValue, kTargetOutput - kInitialValue};
    double controlSignal = 1.0;
    std::vector<double> controlSignals = {controlSignal, controlSignal};

    // Цикл моделирования
    while (std::fabs(kTargetOutput - systemOutputs.back()) > 0.01) {
        double currentError = kTargetOutput - systemOutputs.back();
        errors.push_back(currentError);

        // Проверяем длину ошибок, добавляем нули при необходимости
        while (errors.size() < 3) {
            errors.insert(errors.begin(), 0.0);
        }

        // Рассчитываем новый контрольный сигнал
        controlSignal += kParam1 * errors.back() + kParam2 * errors[errors.size() - 2] + kParam3 * errors[errors.size() - 3];
        controlSignals.push_back(controlSignal);

        // Вычисляем следующий выход системы
        double nextOutput = kAlpha * systemOutputs.back() - kBeta * systemOutputs[systemOutputs.size() - 2] + kGamma * controlSignal + kDelta * std::sin(controlSignal);
        systemOutputs.push_back(nextOutput);
    }

    // Вывод данных
    std::cout << std::setw(12) << "Step"
              << std::setw(12) << "Output"
              << std::setw(12) << "Error"
              << std::setw(12) << "Control" << std::endl;

    for (size_t i = 0; i < systemOutputs.size(); ++i) {
        double error = (i < errors.size()) ? errors[i] : 0.0;
        double control = (i < controlSignals.size()) ? controlSignals[i] : 0.0;
        std::cout << std::setw(12) << i + 1
                  << std::setw(12) << systemOutputs[i]
                  << std::setw(12) << error
                  << std::setw(12) << control << std::endl;
    }
}

int main() {
    // Установка локали для поддержки русского текста
    std::locale::global(std::locale(""));

    SimulateControlSystem();
    return 0;
}
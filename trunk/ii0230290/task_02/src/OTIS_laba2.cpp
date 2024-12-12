#include <iostream>
#include <cmath>
#include <array>
#include <clocale>
#include <iomanip>

using namespace std;

void runControlLoop() {
    const double proportionalGain = 0.097;     // Пропорциональная составляющая
    const double integralTime = 2.162;  // Интегральная составляющая
    const double derivativeTime = 1.0;         // Дифференциальная составляющая
    const double stepSize = 0.0001;      // Шаг

    // Коэффициенты для вычисления
    const double coeff_0 = proportionalGain * (1.0 + (stepSize != 0 ? derivativeTime / stepSize : 0.0));
    const double coeff_1 = -proportionalGain * (1.0 + 2.0 * derivativeTime / stepSize - stepSize / integralTime);
    const double coeff_2 = (proportionalGain * derivativeTime) / stepSize;

    const int iterations = 10;       // Количество итераций
    const double setPoint = 29.0;     // Целевое значение

    cout << "Начало" << std::endl;
    cout << setw(8) << "Итерация" << setw(20) << "Выход" << setw(20) << "Управление" << endl;

    // Параметры линейной модели
    const double modelA = 0.7;
    const double modelB = 0.2;
    double outputValue = 0.0;
    double controlSignal = 0.0;

    // Лямбда-функция для линейной модели
    auto linearModel = [&](double output, double a, double b, double control) {
        return a * output + b * control; // Формула линейной модели
        };

    // Массив для хранения ошибок
    array<double, 3> errors = { 0.0 };

    // Цикл вычисления выходного значения для линейной модели
    for (int i = 1; i <= iterations; i++) {
        errors[2] = errors[1];
        errors[1] = abs(setPoint - outputValue);
        const double deltaControl = coeff_0 * errors[1] + coeff_1 * errors[2] + coeff_2 * errors[0]; // Вычисление изменения управляющего сигнала
        const double previousControl = controlSignal;
        controlSignal = previousControl + deltaControl;
        outputValue = linearModel(outputValue, modelA, modelB, controlSignal); // Вычисление текущего значения

        // Вывод результатов в столбиках
        cout << setw(8) << i << setw(22) << outputValue << setw(20) << controlSignal << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    runControlLoop();
    return 0;
}

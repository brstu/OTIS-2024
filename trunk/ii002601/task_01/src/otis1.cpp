#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double coefficients[] = { 0.8, 0.6, 0.4, 2.2 }; // Коэффициенты для моделирования
const double u = 0.8;

// Функция для расчета линейной модели
vector<double> calculateLinearModel(int steps, double initialTemperature) {
    vector<double> results(steps);
    results[0] = initialTemperature; // Устанавливаем начальное значение

    for (int t = 1; t < steps; ++t) {
        results[t] = coefficients[0] * results[t - 1] + coefficients[1] * u; // Формула линейной модели
    }
    return results;
}

// Функция для расчета нелинейной модели
vector<double> calculateNonlinearModel(int steps, double initialTemperature) {
    vector<double> results(steps);
    results[0] = initialTemperature; // Устанавливаем начальное значение

    if (steps > 1) {
        results[1] = coefficients[0] * results[0] + coefficients[2] * u + coefficients[3] * sin(u); // Вычисляем y1 для второго шага
    }

    for (int t = 2; t < steps; ++t) {
        results[t] = coefficients[0] * results[t - 1] - coefficients[1] * pow(results[t - 2], 2)
            + coefficients[2] * u + coefficients[3] * sin(u); // Формула нелинейной модели
    }
    return results;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double initialTemperature; // Переменная для начальной температуры
    int steps; // Переменная для количества шагов

    // Ввод данных
    cout << "Добро пожаловать в программу моделирования!\n";
    cout << "Пожалуйста, введите начальную температуру: ";
    cin >> initialTemperature;

    cout << "Введите количество шагов (целое положительное число): ";
    cin >> steps;

    // Проверка на корректность ввода количества шагов
    while (steps <= 0) {
        cout << "Количество шагов должно быть положительным. Попробуйте снова: ";
        cin >> steps;
    }

    // Расчет результатов
    vector<double> linearResults = calculateLinearModel(steps + 1, initialTemperature);
    vector<double> nonlinearResults = calculateNonlinearModel(steps + 1, initialTemperature);

    // Вывод результатов для линейной модели
    cout << "\n--- Результаты линейной модели ---\n";
    for (int t = 0; t <= steps; ++t) {
        cout << "Шаг " << t << ": " << linearResults[t] << "\n";
    }

    // Вывод результатов для нелинейной модели
    cout << "\n--- Результаты нелинейной модели ---\n";
    for (int t = 0; t <= steps; ++t) {
        cout << "Шаг " << t << ": " << nonlinearResults[t] << "\n";
    }

    return 0;
}
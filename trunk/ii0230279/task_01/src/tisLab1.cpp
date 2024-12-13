#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Константы для модели
const double a = 0.7;
const double b = 0.6;
const double c = 0.2;
const double d = 5;

// Функция линейной модели
void LinearModel(int Steps, double Y0, double U, double YT) {
    vector<double> temperaturesLinear; // Вектор для хранения температур
    double y = Y0; // Начальное значение температуры

    // Цикл для расчета температуры в каждом шаге
    for (int tau = 0; tau < Steps; ++tau) {
        U = U + YT; // Обновление управляющего сигнала
        y = a * y + b * U; // Расчет новой температуры
        temperaturesLinear.push_back(y); // Сохранение температуры в вектор
    }

    // Вывод результатов линейной модели
    cout << "Линейные модель температуры:\n";
    for (size_t i = 0; i < temperaturesLinear.size(); ++i) {
        cout << "Время " << i + 1 << ": " << temperaturesLinear[i] << "\n"; // Вывод температуры в каждый момент времени
    }
}

// Функция нелинейной модели
void NonlinearModel(int Steps, double Y0, double U, double YT) {
    vector<double> temperaturesNonlinear; // Вектор для хранения температур
    double y = Y0; // Начальное значение температуры
    double y_prev = Y0; // Предыдущее значение температуры

    // Цикл для расчета температуры в каждом шаге
    for (int tau = 0; tau < Steps; ++tau) {
        U = U + YT; // Обновление управляющего сигнала
        y = a * y - b * y_prev * y_prev + c * U + d * sin(U - 1); // Расчет новой температуры с учетом нелинейностей
        temperaturesNonlinear.push_back(y); // Сохранение температуры в вектор
        y_prev = y; // Обновление предшествующей температуры
    }

    // Вывод результатов нелинейной модели
    cout << "Нелинейной модель температуры:\n";
    for (size_t i = 0; i < temperaturesNonlinear.size(); ++i) {
        cout << "Время " << i + 1 << ": " << temperaturesNonlinear[i] << "\n"; // Вывод температуры в каждый момент времени
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int Steps = 7; // Количество шагов
    double Y0 = 30; // Начальная температура
    double U = 5; // Начальное значение управляющего сигнала
    double YT = 1.5; // Шаг изменения управляющего сигнала
    LinearModel(Steps, Y0, U, YT); // Вызов линейной модели
    NonlinearModel(Steps, Y0, U, YT); // Вызов нелинейной модели

    return 0; // Завершение программы
}
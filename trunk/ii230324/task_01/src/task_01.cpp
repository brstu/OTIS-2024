#include <iostream>
#include <cmath>

using namespace std;

// Константы
const double a = 0.5;
const double b = 0.001;
const double c = 0.3;
const double d = 0.5;

// Функция для линейной модели
void linearModel(double u, int steps, double y) {
    for (int i = 1; i <= steps; ++i) {
        cout << "Time: " << i << ", Linear Output: " << y << endl;
        y = a * y + b * u; // Обновление значения
    }
    cout << "---------------------\n";
}

// Функция для нелинейной модели
void nonlinearModel(double u, int steps, double y, double y1) {
    for (int i = 1; i <= steps; ++i) {
        cout << "Time: " << i << ", Nonlinear Output: " << y << endl;
        double newY = a * y - b * y1 * y1 + c * u + d * sin(u); // Обновление значения
        y1 = y; // Сохранение предыдущего значения
        y = newY; // Обновление текущего значения
    }
}

int main() {
    double u;      // входное тепло
    int steps=30;     // количество шагов
    double y;      // начальное значение для линейной модели
    double y1;     // начальное значение для нелинейной модели

    // Ввод данных с клавиатуры
    cout << "Введите входное тепло (u): ";
    cin >> u;
    cout << "Введите начальное значение для линейной модели (y): ";
    cin >> y;
    cout << "Введите начальное значение для нелинейной модели (y1): ";
    cin >> y1;

    cout << "Линейная модель: \n";
    linearModel(u, steps, y);

    cout << "Нелинейная модель: \n";
    nonlinearModel(u, steps, y, y1);

    return 0;
}
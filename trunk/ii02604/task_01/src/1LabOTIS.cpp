#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double a = 0.8;
const double b = 0.6;
const double c = 0.4;
const double d = 2.2;
const double u = 0.8;

// Функция для расчета линейной модели
vector<double> liney(int step, double tem) {
    vector<double> result(step);
    result[0] = tem; // Устанавливаем начальное значение
    for (int t = 1; t < step; ++t) {
        result[t] = a * result[t - 1] + b * u; // Формула линейной модели
    }
    return result;
}

// Функция для расчета нелинейной модели
vector<double> noliney(int step, double tem) {
    vector<double> result(step);
    result[0] = tem; // Устанавливаем начальное значение

    if (step > 1) {
        result[1] = a * result[0] + c * u + d * sin(u); // Вычисляем y1 для второго шага
    }
    for (int t = 2; t < step; ++t) {
        result[t] = a * result[t - 1] - b * pow(result[t - 2], 2) + c * u + d * sin(u); // Формула нелинейной модели
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double tem; // Переменная для начальной температуры
    int step; // Переменная для количества шагов

    // Ввод данных
    cout << "Введите начальную температуру: ";
    cin >> tem;
    cout << "Введите количество шагов: ";
    cin >> step;

    // Вычисляем результаты для обеих моделей
    vector<double> lineyres = liney(step + 1, tem);
    vector<double> nolineyres = noliney(step + 1, tem);

    // Вывод результатов для линейной модели
    cout << "Линейная модель:\n";
    for (int t = 0; t <= step; ++t) {
        cout << lineyres[t] << "\n";
    }

    // Вывод результатов для нелинейной модели
    cout << "Нелинейная модель:\n";
    for (int t = 0; t <= step; ++t) {
        cout << nolineyres[t] << "\n";
    }

    return 0;
}
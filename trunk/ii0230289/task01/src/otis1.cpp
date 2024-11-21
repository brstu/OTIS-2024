#include <iostream>
#include <cmath>
using namespace std;
// Функция для линейного шага модели
double linMStep(double a, double b, double y, double u) {
    return a * y + b * u;
}
// Функция для нелинейного шага модели
double nonlinMStep(double a, double b, double c, double d, double y, double y_prev, double u) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u);
}
// Функция для симуляции линейной и нелинейной модели
void simulation(double a, double b, double c, double d, double y0, double u0, int num_steps) {
    double y_linear = y0;
    double y_nonlinear = y0;
    double y_prev = y0;
    double u = u0;
    cout << "Результаты (Линейная модель):n";
    for (int t = 0; t < num_steps; ++t) {
        y_linear = linMStep(a, b, y_linear, u);
        cout << "Шаг = " << t << " Температура = " << y_linear << endl;
    }
    cout << "nРезультаты (Нелинейная модель):n";
    for (int t = 0; t < num_steps; ++t) {
        double y_next = nonlinMStep(a, b, c, d, y_nonlinear, y_prev, u);
        cout << "Шаг = " << t << " Температура = " << y_next << endl;
        y_prev = y_nonlinear;
        y_nonlinear = y_next;
    }
}
// Главная функция
int main() {
    setlocale(LC_ALL, "RU");
    // Ввод параметров от пользователя
    double a, b, c, d;
    double initial_temperature, initial_input;
    int num_steps;
    cout << "Введите значение параметра a: ";
    cin >> a;
    cout << "Введите значение параметра b: ";
    cin >> b;
    cout << "Введите значение параметра c (для нелинейной модели): ";
    cin >> c;
    cout << "Введите значение параметра d (для нелинейной модели): ";
    cin >> d;
    cout << "Введите начальное значение температуры y0: ";
    cin >> initial_temperature;
    cout << "Введите начальное значение управляющего сигнала u0: ";
    cin >> initial_input;
    cout << "Введите количество шагов моделирования: ";
    cin >> num_steps;
    // Запуск симуляции
    simulation(a, b, c, d, initial_temperature, initial_input, num_steps);
    return 0;
}
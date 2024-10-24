#include <iostream>
#include <cmath> // Для функции sin()
using namespace std;

// Линейная модель: y(t+1) = a * y(t) + b * u(t)
void simulateLinearModel(double a, double b, double y0, double u0, int num_steps) {
    double y = y0; // Начальная температура
    double u = u0; // Начальный управляющий сигнал

    cout << "Линейная модель:\n";
    for (int t = 0; t < num_steps; ++t) {
        double y_next = a * y + b * u;
        cout << "Шаг времени " << t << ": Температура = " << y_next << std::endl;
        y = y_next; // Обновляем температуру
    }
}

// Нелинейная модель: y(t+1) = a * y(t) - b * y^2(t-1) + c * u(t) + d * sin(u(t))
void simulateNonlinearModel(double a, double b, double c, double d, double y0, double u0, int num_steps) {
    double y_prev = y0; // Температура на шаге t-1
    double y = y0; // Начальная температура
    double u = u0; // Начальный управляющий сигнал

    cout << "\nНелинейная модель:\n";
    for (int t = 0; t < num_steps; ++t) {
        double y_next = a * y - b * y_prev * y_prev + c * u + d * sin(u);
        cout << "Шаг времени " << t << ": Температура = " << y_next << std::endl;
        y_prev = y; // Обновляем y(t-1)
        y = y_next; // Обновляем y(t)
    }
}

int main()
{
    // Переменные для входных данных
    double a, b, c, d;
    double initial_temperature, initial_input;
    int num_steps;

    // Ввод данных
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

    // Запуск симуляций
    simulateLinearModel(a, b, initial_temperature, initial_input, num_steps);
    simulateNonlinearModel(a, b, c, d, initial_temperature, initial_input, num_steps);

    return 0;
}
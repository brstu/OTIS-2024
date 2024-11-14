#include <iostream>
#include <cmath> 
using namespace std;

void runLinearSimulation(double alpha, double beta, double temp0, double control0, int steps_count) {
    double current_temp = temp0;
    double control_signal = control0;

    cout << "Линейная модель:\n";
    for (int step = 0; step < steps_count; ++step) {
        double next_temp = alpha * current_temp + beta * control_signal;
        cout << "Шаг времени " << step << ": Температура = " << next_temp << std::endl;
        current_temp = next_temp;
    }
}

void runNonlinearSimulation(double alpha, double beta, double gamma, double delta, double temp0, double control0, int steps_count) {
    double prev_temp = temp0;
    double current_temp = temp0;
    double control_signal = control0;

    cout << "\nНелинейная модель:\n";
    for (int step = 0; step < steps_count; ++step) {
        double next_temp = alpha * current_temp - beta * prev_temp * prev_temp + gamma * control_signal + delta * sin(control_signal);
        cout << "Шаг времени " << step << ": Температура = " << next_temp << std::endl;
        prev_temp = current_temp;
        current_temp = next_temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double alpha, beta, gamma, delta;
    double start_temp, start_control;
    int steps_count;

    cout << "Введите значение параметра alpha: ";
    cin >> alpha;

    cout << "Введите значение параметра beta: ";
    cin >> beta;

    cout << "Введите значение параметра gamma (для нелинейной модели): ";
    cin >> gamma;

    cout << "Введите значение параметра delta (для нелинейной модели): ";
    cin >> delta;

    cout << "Введите начальное значение температуры temp0: ";
    cin >> start_temp;

    cout << "Введите начальное значение управляющего сигнала control0: ";
    cin >> start_control;

    cout << "Введите количество шагов моделирования: ";
    cin >> steps_count;

    runLinearSimulation(alpha, beta, start_temp, start_control, steps_count);
    runNonlinearSimulation(alpha, beta, gamma, delta, start_temp, start_control, steps_count);

    return 0;

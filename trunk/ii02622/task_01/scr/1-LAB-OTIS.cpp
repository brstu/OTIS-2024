#include <iostream>
#include <cmath>
using namespace std;

double computeLinearStep(double alpha, double beta, double temp, double control) {
    return alpha * temp + beta * control;
}

double computeNonlinearStep(double alpha, double beta, double gamma, double delta, double temp, double prev_temp, double control) {
    return alpha * temp - beta * prev_temp * prev_temp + gamma * control + delta * sin(control);
}

void performSimulation(double alpha, double beta, double gamma, double delta, double initial_temp, double initial_control, int steps) {
    double linear_temp = initial_temp;
    double control_signal = initial_control;

    cout << "Результаты линейной модели:\n";
    for (int step = 0; step < steps; ++step) {
        double next_temp = computeLinearStep(alpha, beta, linear_temp, control_signal);
        cout << "Шаг " << step << ": Температура = " << next_temp << endl;
        linear_temp = next_temp;
    }

    double prev_temp = initial_temp;
    double nonlinear_temp = initial_temp;

    cout << "\nРезультаты нелинейной модели:\n";
    for (int step = 0; step < steps; ++step) {
        double next_temp = computeNonlinearStep(alpha, beta, gamma, delta, nonlinear_temp, prev_temp, control_signal);
        cout << "Шаг " << step << ": Температура = " << next_temp << endl;
        prev_temp = nonlinear_temp;
        nonlinear_temp = next_temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double alpha, beta, gamma, delta;
    double init_temp, init_control;
    int steps;

    cout << "Введите значение параметра alpha: ";
    cin >> alpha;
    cout << "Введите значение параметра beta: ";
    cin >> beta;
    cout << "Введите значение параметра gamma (для нелинейной модели): ";
    cin >> gamma;
    cout << "Введите значение параметра delta (для нелинейной модели): ";
    cin >> delta;
    cout << "Введите начальное значение температуры: ";
    cin >> init_temp;
    cout << "Введите начальное значение управляющего сигнала: ";
    cin >> init_control;
    cout << "Введите количество шагов моделирования: ";
    cin >> steps;

    performSimulation(alpha, beta, gamma, delta, init_temp, init_control, steps);

    return 0;
}

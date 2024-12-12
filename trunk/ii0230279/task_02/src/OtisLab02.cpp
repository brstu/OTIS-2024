#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // Определение констант
    float alpha = 0.9, beta = 0.4, gamma = 0.45, delta = 0.74;
    float K = 0.9, initial_time = 0.3, sample_time = 1.0, delay_time = 0.1, output = 10.0;

    // Калкулирование начальных условий
    float q0 = K * (1 + (delay_time / initial_time)), q1 = -K * (1 + 2 * (delay_time / initial_time) - (initial_time / sample_time)), q2 = K * (delay_time / initial_time);

    // Инициализация массивов
    const short int n_iterations = 2;
    vector<float> result(n_iterations, 0.0);
    vector<float> error(n_iterations, 0.0);
    vector<float> control(n_iterations, 1.0);

    // Установка русского языка для вывода
    setlocale(LC_ALL, "RUSSIAN");

    // Главный цикл
    while (abs(output - result.back()) > 1) {
        // Калкулирование ошибки
        error.push_back(output - result.back());

        // Калкулирование контроля
        float new_control = control.back() + q0 * error.back() + q1 * error[error.size() - 2] + q2 * error[error.size() - 3];
        control.push_back(new_control);

        // Калкулирование нового результата
        result.push_back(alpha * result.back() - beta * result[result.size() - 2] + gamma * control.back() + delta * sin(control.back()));
    }

    // Вывод результатов
    cout << right << setw(9) << "Итерация" << setw(9) << right << "Выход" << setw(12) << right << "Ошибка" << setw(12) << right << "Контроль" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << right << setw(9) << i + 1 << setw(9) << result[i] << setw(12) << error[i] << setw(12) << control[i] << endl;
    }

    return 0;
}
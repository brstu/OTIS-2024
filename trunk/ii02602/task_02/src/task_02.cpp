#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>  // Для форматирования вывода
using namespace std;

// Коэффициенты системы
double coeff_a, coeff_b, coeff_c, coeff_d;
// Параметры системы
double gain, time_const_0, time_delay, time_const, desired_output;
// Параметры регулятора
double reg_0, reg_1, reg_2;

void simulate_system() {
    const double initial_output = 2.0;  // Начальное значение выхода
    double control_signal = 1.0;        // Управляющий сигнал
    vector<double> output = { initial_output };  // Вектор выходных значений
    vector<double> error = { desired_output - initial_output };  // Вектор ошибок
    vector<double> control_history = { control_signal };  // История управляющего сигнала

    // Цикл продолжается, пока ошибка не станет меньше 0.01
    while (fabs(error.back()) > 0.01) {
        // Вычисление новой ошибки
        error.push_back(desired_output - output.back());

        // Вычисление нового управляющего сигнала
        control_signal = control_history.back()
            + reg_0 * error.back()
            + reg_1 * (error.size() > 1 ? error[error.size() - 2] : 0)
            + reg_2 * (error.size() > 2 ? error[error.size() - 3] : 0);

        // Обновление выходного значения системы
        double new_output = coeff_a * output.back()
            - coeff_b * (output.size() > 1 ? output[output.size() - 2] : 0)
            + coeff_c * control_signal
            + coeff_d * sin(control_history.back());

        output.push_back(new_output);  // Добавляем новое значение в вектор выходов
        control_history.push_back(control_signal);  // Сохраняем управляющий сигнал
    }

    // Вывод результатов
    cout << fixed << setprecision(4);  // Форматирование вывода с 4 знаками после запятой
    cout << "Step\tOutput\tError\tControl Signal\n";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << i + 1 << "\t"
            << output[i] << "\t"
            << error[i] << "\t"
            << control_history[i] << endl;
    }
}

int main() {
    // Ввод параметров системы
    setlocale(LC_ALL, "RU");
    cout << "Введите коэффициенты системы:\n";
    cout << "coeff_a: "; cin >> coeff_a;
    cout << "coeff_b: "; cin >> coeff_b;
    cout << "coeff_c: "; cin >> coeff_c;
    cout << "coeff_d: "; cin >> coeff_d;

    cout << "\nВведите параметры системы:\n";
    cout << "gain: "; cin >> gain;
    cout << "time_const_0: "; cin >> time_const_0;
    cout << "time_delay: "; cin >> time_delay;
    cout << "time_const: "; cin >> time_const;
    cout << "desired_output (желаемое значение выхода): "; cin >> desired_output;

    // Расчет параметров регулятора
    reg_0 = gain * (1 + (time_delay / time_const_0));
    reg_1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
    reg_2 = gain * (time_delay / time_const_0);

    // Запуск симуляции системы
    simulate_system();

    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double system_coeff_a, system_coeff_b, system_coeff_c, system_coeff_d; // Коэффициенты системы
double system_gain, time_constant_0, system_delay, time_constant, target_output; // Параметры системы
double controller_k0, controller_k1, controller_k2; // Параметры регулятора
void run_simulation() {
    const double initial_value = 2.0; // Начальное значение выхода
    double control_signal = 1.0;      // Управляющий сигнал

    vector<double> outputs = { initial_value }; // Вектор выходных значений
    vector<double> errors = { target_output - initial_value }; // Вектор ошибок
    vector<double> control_signals = { control_signal }; // История управляющего сигнала

    while (fabs(errors.back()) > 0.01) {
        // Вычисляем текущую ошибку
        errors.push_back(target_output - outputs.back());

        // Вычисляем новый управляющий сигнал
        control_signal = control_signals.back()
            + controller_k0 * errors.back()
            + controller_k1 * (errors.size() > 1 ? errors[errors.size() - 2] : 0)
            + controller_k2 * (errors.size() > 2 ? errors[errors.size() - 3] : 0);

        // Обновляем выход системы
        double new_output = system_coeff_a * outputs.back()
            - system_coeff_b * (outputs.size() > 1 ? outputs[outputs.size() - 2] : 0)
            + system_coeff_c * control_signal
            + system_coeff_d * sin(control_signals.back());
        outputs.push_back(new_output);
        control_signals.push_back(control_signal);
    }
    cout << fixed << setprecision(4);
    cout << "Step\tOutput\t\tError\t\tControl Signal\n";
    for (size_t i = 0; i < outputs.size(); ++i) {
        cout << i + 1 << "\t"
            << outputs[i] << "\t\t"
            << errors[i] << "\t\t"
            << (i < control_signals.size() ? control_signals[i] : 0) << endl;
    }
}

void initialize_parameters() {
    setlocale(LC_ALL, "RU");

    cout << "Введите коэффициенты системы:\n";
    cout << "system_coeff_a: "; cin >> system_coeff_a;
    cout << "system_coeff_b: "; cin >> system_coeff_b;
    cout << "system_coeff_c: "; cin >> system_coeff_c;
    cout << "system_coeff_d: "; cin >> system_coeff_d;

    cout << "\nВведите параметры системы:\n";
    cout << "system_gain: "; cin >> system_gain;
    cout << "time_constant_0: "; cin >> time_constant_0;
    cout << "system_delay: "; cin >> system_delay;
    cout << "time_constant: "; cin >> time_constant;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    controller_k0 = system_gain * (1 + (system_delay / time_constant_0));
    controller_k1 = -system_gain * (1 + 2 * (system_delay / time_constant_0) - (time_constant_0 / time_constant));
    controller_k2 = system_gain * (system_delay / time_constant_0);
}

int main() {
    initialize_parameters(); // Ввод параметров системы
    run_simulation();        // Запуск симуляции
    return 0;
}

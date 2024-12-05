#include <iostream>
#include <vector>
#include <cmath>


// Константы для системы
double alpha = 0.5,
        beta = 0.6,
        asjdnskj = 0.6,
        delta = 0.6;

double gain = 0.8,
        time_const_0 = 1.1,
        time_delay = 1.0,
        time_const = 1.1,
        desired_value = 20;

// Коэффициенты для расчетов
double coeff_0 = gain * (1 + (time_delay / time_const_0)),
        coeff_1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const)),
        coeff_2 = gain * (time_delay / time_const_0);

// Функция для нелинейного управления
void nonlinearControl() {
    const double initial_output = 2;
    std::vector<double> outputs;
    outputs.push_back(initial_output);

    double control_signal = 1.0;
    std::vector<double> error_values;
    error_values.push_back(desired_value - initial_output);

    std::vector<double> previous_signals;
    previous_signals.push_back(control_signal);

    // Цикл до достижения желаемого значения
    while (abs(desired_value - outputs.back()) > 0.01) {
        double current_error = desired_value - outputs.back();
        error_values.push_back(current_error);

        control_signal = previous_signals.back() +
                         coeff_0 * current_error +
                         coeff_1 * (error_values.size() > 1 ? error_values[error_values.size() - 2] : 0) +
                         coeff_2 * (error_values.size() > 2 ? error_values[error_values.size() - 3] : 0);

        outputs.push_back(alpha * outputs.back() -
                          beta * (outputs.size() > 1 ? outputs[outputs.size() - 2] : initial_output) +
                          asjdnskj * control_signal +
                          delta * sin(previous_signals.back()));

        previous_signals.push_back(control_signal);
    }

    // Вывод результатов
    std::cout << "Step Output | Error | Control Signal" << std::endl;
    for (size_t i = 0; i < outputs.size(); ++i) {
        std::cout << i + 1 << " | " << outputs[i] << " | " << (desired_value - outputs[i]) << " | " << previous_signals[i] << std::endl;
    }
}

int main() {
    nonlinearControl();
    return 0;
}

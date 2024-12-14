#include <iostream>
#include <cmath>

using namespace std;

struct PIDParameters {
    double proportional_gain;
    double integral_gain;
    double derivative_gain;
    double coefficient_K;
    double time_constant_T;
    double derivative_time_TD;
    double sampling_interval_T0;
};

double computeControlSignal(double target, double current_value, double time_step, PIDParameters& pid_params, double& previous_error, double& integral_term) {
    double current_error = target - current_value;
    integral_term += current_error * time_step;
    double derivative_term = (current_error - previous_error) / time_step;

    double control_signal = pid_params.proportional_gain * current_error
        + pid_params.integral_gain * integral_term
        + pid_params.derivative_gain * derivative_term;

    previous_error = current_error;
    return control_signal;
}

int main() {
    PIDParameters params = { 1.0, 0.1, 0.05, 0.8, 100.0, 100.0, 1.1 };

    double target_value = 100.0;  // Целевая величина
    double current_value = 90.0; // Текущее значение
    double time_step = 0.1;      // Интервал времени
    double previous_error = 0.0; // Предыдущая ошибка
    double integral_term = 0.0;  // Интегральная составляющая

    for (int iteration = 0; iteration < 100; ++iteration) {
        double control_signal = computeControlSignal(target_value, current_value, time_step, params, previous_error, integral_term);

        cout << "Iteration " << iteration << ": Control Signal = " << control_signal << endl;

        current_value += control_signal * 0.1;
    }

    return 0;
}


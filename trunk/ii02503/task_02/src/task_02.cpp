#include <iostream>

struct PIDConfig {
    double proportional_gain; // коэффициент пропорциональности
    double integral_gain;     // коэффициент интегрирования
    double derivative_gain;   // коэффициент дифференцирования
    double small_constant;    // малое значение для предотвращения деления на ноль
    double sample_time;       // время дискретизации
    double derivative_time;   // время дифференцирования
    double initial_time;      // начальное время
};

double computeControlSignal(double target_value, double current_value, double delta_time, PIDConfig& config, double& last_error, double& accumulated_error) {
    double error = target_value - current_value;
    accumulated_error += error * delta_time;
    double rate_of_change = (error - last_error) / delta_time;

    double control_signal = config.proportional_gain * error + config.integral_gain * accumulated_error + config.derivative_gain * rate_of_change;

    last_error = error;
    return control_signal;
}

void initializePIDConfig(PIDConfig& config) {
    config.proportional_gain = 1.0;
    config.integral_gain = 0.1;
    config.derivative_gain = 0.05;
    config.small_constant = 0.0001;
    config.sample_time = 100;
    config.derivative_time = 100;
    config.initial_time = 1;
}

void runControlLoop(double target_value, double& current_value, double delta_time, PIDConfig& config) {
    double last_error = 0.0;
    double accumulated_error = 0.0;

    for (int i = 0; i < 100; ++i) {
        double control_signal = computeControlSignal(target_value, current_value, delta_time, config, last_error, accumulated_error);
        std::cout << control_signal << std::endl;

        // Обновление текущего значения
        current_value += control_signal * 0.1;
    }
}

int main() {
    PIDConfig pid_config;
    initializePIDConfig(pid_config);

    double target_value = 100.0;       // целевое значение
    double current_value = 90.0;       // текущее значение
    double delta_time = 0.1;           // время дискретизации

    runControlLoop(target_value, current_value, delta_time, pid_config);

    return 0;
}

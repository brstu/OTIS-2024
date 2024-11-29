#include <iostream>

struct PIDConfig {
    double proportional;
    double integral;
    double derivative;
    double gain;
    double sampling_time;
    double derivative_time;
    double initial_time;
};

double computeControl(double target, double current, double delta_time, PIDConfig& config, double& last_error, double& accumulated_error) {
    double error = target - current;
    accumulated_error += error * delta_time;
    double rate_of_change = (error - last_error) / delta_time;

    double output_signal = config.proportional * error + config.integral * accumulated_error + config.derivative * rate_of_change;

    last_error = error;
    return output_signal;
}

int main() {
    PIDConfig config = { 1.0, 0.1, 0.05, 0.0001, 100, 100, 1 };

    double target_value = 100.0;
    double current_value = 90.0;
    double delta_time = 0.1;

    double last_error = 0.0;
    double accumulated_error = 0.0;

    for (int step = 0; step < 100; ++step) {
        double control_signal = computeControl(target_value, current_value, delta_time, config, last_error, accumulated_error);
        std::cout << control_signal << std::endl;

        current_value += control_signal * 0.1;
    }

    return 0;
}
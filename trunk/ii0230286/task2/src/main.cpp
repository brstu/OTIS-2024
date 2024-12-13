#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// System coefficients
const double system_coefficient_a = 0.9;
const double system_coefficient_b = 0.3;
const double system_coefficient_c = 0.4;
const double system_coefficient_d = 0.1;

// System parameters
const double system_parameter_trans_coeff_K = 0.9;
const double system_parameter_time0 = 0.5, system_parameter_timeC = 1.0, system_parameter_timeD = 0.5;
const double system_target_output = 20;

// Controller parameters
const double controller_gain_1 = system_parameter_trans_coeff_K * (1 + (system_parameter_timeD / system_parameter_time0));
const double controller_gain_2 = -system_parameter_trans_coeff_K * (1 + 2 * (system_parameter_timeD / system_parameter_time0) - (system_parameter_time0 / system_parameter_timeC));
const double controller_gain_3 = system_parameter_trans_coeff_K * (system_parameter_timeD / system_parameter_time0);

void RunNonlinearModel() {
    // Initial values
    const short int initial_model_output_value = 2;
    std::vector<double> model_output_values = { initial_model_output_value, initial_model_output_value }; // Model output vector
    std::vector<double> error_values = { system_target_output - initial_model_output_value, system_target_output - initial_model_output_value }; // Error vector
    double control_signal_value = 1;
    std::vector<double> control_signal_values = { control_signal_value, control_signal_value }; // Control signal vector

    // Simulation loop
    while (std::abs(system_target_output - model_output_values.back()) > 0.01) {
        // Update error
        error_values.push_back(system_target_output - model_output_values.back());

        // Calculate control signal
        control_signal_value += controller_gain_1 * error_values.back() + controller_gain_2 * error_values[error_values.size() - 2] + controller_gain_3 * error_values[error_values.size() - 3];
        control_signal_values.push_back(control_signal_value);

        // Update model output
        model_output_values.push_back(system_coefficient_a * model_output_values.back() - system_coefficient_b * model_output_values[model_output_values.size() - 2] + system_coefficient_c * control_signal_value + system_coefficient_d * std::sin(control_signal_values.back()));
    }

    // Output results
    std::cout << std::right << std::setw(10) << "Iteration"
        << std::setw(10) << "Output"
        << std::setw(13) << "Error"
        << std::setw(13) << "Control" << std::endl;

    for (size_t i = 0; i < model_output_values.size(); ++i) {
        std::cout << std::right << std::setw(10) << i + 1
            << std::setw(10) << model_output_values[i]
            << std::setw(13) << error_values[i]
            << std::setw(13) << control_signal_values[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    RunNonlinearModel();
    return 0;
}
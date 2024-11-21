#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// System coefficients
double system_coeff_a, system_coeff_b, system_coeff_c, system_coeff_d;
// System parameters
double controller_gain, time_constant_0, time_delay, time_constant, target_output;
// Controller parameters
double controller_param_0, controller_param_1, controller_param_2;

void simulate_nonlinear_system() {
    // Initial parameters
    const short int initial_output_value = 2;
    vector<double> system_output = { initial_output_value, initial_output_value };  // Output values
    double control_signal = 1.0;  // Control signal
    vector<double> error_values = { target_output - initial_output_value, target_output - initial_output_value };  // Error
    vector<double> previous_control_signals = { control_signal, control_signal };  // Previous control signal values

    // Loop until error is smaller than the threshold
    while (abs(target_output - system_output.back()) > 0.01)
    {
        error_values.push_back(target_output - system_output.back());  // Update error
        control_signal = previous_control_signals.back() + controller_param_0 * error_values.back() + controller_param_1 * error_values[error_values.size() - 2] + controller_param_2 * error_values[error_values.size() - 3];
        // Calculate new system output value
        system_output.push_back(system_coeff_a * system_output.back() - system_coeff_b * system_output[system_output.size() - 2] + system_coeff_c * control_signal + system_coeff_d * sin(previous_control_signals.back()));
        previous_control_signals.push_back(control_signal);  // Save control signal
    }

    // Output results
    cout << "Step\tOutput\tError\tControl Signal\n";
    for (int i = 0; i < system_output.size(); i++)
        cout << i + 1 << ";" << system_output[i] << ";" << error_values[i] << ";" << previous_control_signals[i] << endl;
}

int main() {
    // Input system coefficients
    cout << "Enter system coefficients:\n";
    cout << "system_coeff_a: "; cin >> system_coeff_a;
    cout << "system_coeff_b: "; cin >> system_coeff_b;
    cout << "system_coeff_c: "; cin >> system_coeff_c;
    cout << "system_coeff_d: "; cin >> system_coeff_d;

    // Input system parameters
    cout << "Enter system parameters:\n";
    cout << "controller_gain: "; cin >> controller_gain;
    cout << "time_constant_0: "; cin >> time_constant_0;
    cout << "time_delay: "; cin >> time_delay;
    cout << "time_constant: "; cin >> time_constant;
    cout << "target_output (desired output value): "; cin >> target_output;

    // Calculate controller parameters
    controller_param_0 = controller_gain * (1 + (time_delay / time_constant_0));
    controller_param_1 = -controller_gain * (1 + 2 * (time_delay / time_constant_0) - (time_constant_0 / time_constant));
    controller_param_2 = controller_gain * (time_delay / time_constant_0);

    // Run simulation
    simulate_nonlinear_system();

    return 0;
}

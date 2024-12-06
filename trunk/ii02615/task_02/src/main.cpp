#include <iostream>
#include <vector>
#include <cmath>

double coeff_a, coeff_b, coeff_c, coeff_d;
double gain, time_const_0, time_delay, time_const, desired_output;
double response_0, response_1, response_2;

void process_system() {
    const short int initial_output = 2;
    std::vector<double> results = { initial_output, initial_output }; 
    double control_signal = 1.0; 
    std::vector<double> deviations = { desired_output - initial_output, desired_output - initial_output }; 
    std::vector<double> previous_control = { control_signal, control_signal }; 

    while (std::abs(desired_output - results.back()) > 0.01) {
        deviations.push_back(desired_output - results.back());
        control_signal = previous_control.back() + response_0 * deviations.back() +
                         response_1 * deviations[deviations.size() - 2] +
                         response_2 * deviations[deviations.size() - 3];
        results.push_back(coeff_a * results.back() - coeff_b * results[results.size() - 2] +
                          coeff_c * control_signal + coeff_d * std::sin(previous_control.back()));
        previous_control.push_back(control_signal);
    }

    std::cout << "Step\tOutput\tError\tControl Signal\n";
    for (int i =
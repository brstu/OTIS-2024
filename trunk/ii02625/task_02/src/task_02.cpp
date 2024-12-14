#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double gain = 0.001; // Коэффициент передачи
const double integration_constant = 50; // Постоянная интегрирования
const double differentiation_constant = 100; // Постоянная дифференцирования
const double step = 1; // Шаг
const double a_coefficient = 0.4;
const double b_coefficient = 0.4;
const double c_coefficient = 0.4;
const double d_coefficient = 0.4;

void non_linear_system(double desired_value) {
    double q0 = gain * (1 + differentiation_constant / step);
    double q1 = -gain * (1 + 2 * differentiation_constant / step - step / integration_constant);
    double q2 = gain * differentiation_constant / step;
    vector<double> output_values = { 0, 0, 0 };
    vector<double> control_signals = { 1, 1 };

    for (int i = 0; i < integration_constant; i++) {
        double error0 = desired_value - output_values[output_values.size() - 1];
        double error1 = desired_value - output_values[output_values.size() - 2];
        double error2 = desired_value - output_values[output_values.size() - 3];
        double integral_sum = q0 * error0 + q1 * error1 + q2 * error2;
        control_signals[0] = control_signals[1] + integral_sum;
        control_signals[1] = control_signals[0];
        output_values.push_back(a_coefficient * output_values[output_values.size() - 1] -
                                b_coefficient * output_values[output_values.size() - 2] * output_values[output_values.size() - 2] +
                                c_coefficient * control_signals[0] +
                                d_coefficient * sin(control_signals[1]));
    }

    for (double value : output_values) {
        double result = value * desired_value / output_values[output_values.size() - 1];
        cout << result << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    double desired_value;
    cout << "Желаемое начальное значение: ";
    cin >> desired_value;
    non_linear_system(desired_value);
    return 0;
}


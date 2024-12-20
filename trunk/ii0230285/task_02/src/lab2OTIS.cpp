#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double coeff_a, coeff_b, coeff_c, coeff_d;
double gain, time_const_0, time_delay, time_const, desired_output;
double reg_0, reg_1, reg_2;

void updateCoefficients() {
    cout << "Введите коэффициенты системы:\n";
    cout << "coeff_a: "; cin >> coeff_a;
    cout << "coeff_b: "; cin >> coeff_b;
    cout << "coeff_c: "; cin >> coeff_c;
    cout << "coeff_d: "; cin >> coeff_d;
}

void updateSystemParameters() {
    cout << "Введите параметры системы:\n";
    cout << "gain: "; cin >> gain;
    cout << "time_const_0: "; cin >> time_const_0;
    cout << "time_delay: "; cin >> time_delay;
    cout << "time_const: "; cin >> time_const;
    cout << "desired_output (желаемое значение выхода): "; cin >> desired_output;
}

void calculateRegulatorParameters() {
    reg_0 = gain * (1 + (time_delay / time_const_0));
    reg_1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
    reg_2 = gain * (time_delay / time_const_0);
}

void simulateSystem() {
    const short int initial_output = 2;
    vector<double> output = { initial_output, initial_output };
    vector<double> error = { desired_output - initial_output, desired_output - initial_output };
    vector<double> control_signal_history = { 1.0, 1.0 };
    double control_signal = 1.0;

    while (abs(desired_output - output.back()) > 0.01) {
        double current_output = output.back();
        error.push_back(desired_output - current_output);

        control_signal = control_signal_history.back() +
            reg_0 * error.back() +
            reg_1 * error[error.size() - 2] +
            reg_2 * error[error.size() - 3];

        control_signal_history.push_back(control_signal);

        double new_output = coeff_a * current_output -
            coeff_b * output[output.size() - 2] +
            coeff_c * control_signal +
            coeff_d * sin(control_signal_history[control_signal_history.size() - 2]);

        output.push_back(new_output);
    }

    cout << "Step\tOutput\tError\tControl Signal\n";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << control_signal_history[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    updateCoefficients();
    updateSystemParameters();
    calculateRegulatorParameters();
    simulateSystem();

    return 0;
}

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double gain = 0.1;
const double nonlinearity = 2.0;
const double damping = 0.05;


double nonlinear_response(double error, double prev_output) {
    return prev_output + gain * pow(error, nonlinearity) - damping * prev_output;
}


void control_system(double desired_value, int iterations) {
    double current_output = 0.0;

    for (int i = 0; i < iterations; ++i) {
        double error = desired_value - current_output;
        current_output = nonlinear_response(error, current_output);
        cout << "Iteration " << i + 1 << ": Output = " << current_output << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    double desired_value;
    int iterations;

    cout << "Ваше желаемое значение: ";
    cin >> desired_value;
    cout << "Количество итераций: ";
    cin >> iterations;

    control_system(desired_value, iterations);
    return 0;
}
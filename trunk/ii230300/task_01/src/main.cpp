#include <iostream>
#include <cmath>
#include <vector>

const double a_linear = 0.5;
const double b_linear = 0.1;
const double a_nonlinear = 0.6;
const double b_nonlinear = 0.1;
const double c_nonlinear = 0.1;
const double d_nonlinear = 0.05;

double simulate_linear(double y_prev, double u) {
    return a_linear * y_prev + b_linear * u;
}

double simulate_nonlinear(double y_prev, double u) {
    return a_nonlinear * y_prev - b_nonlinear * pow(y_prev - 1, 2) + c_nonlinear * u + d_nonlinear * sin(u - 1);
}

int main() {
    double y_0 = 1;
    double u_0 = 0;

    int num_steps = 10;
    std::vector<double> time(num_steps);
    std::vector<double> y_linear(num_steps);
    std::vector<double> y_nonlinear(num_steps);

    for (int i = 0; i < num_steps; ++i) {
        time[i] = i + 1;
    }

    y_linear[0] = y_0;
    for (int i = 1; i < num_steps; ++i) {
        y_linear[i] = simulate_linear(y_linear[i - 1], u_0);
    }

    y_nonlinear[0] = y_0;
    for (int i = 1; i < num_steps; ++i) {
        y_nonlinear[i] = simulate_nonlinear(y_nonlinear[i - 1], u_0);
    }

    std::cout << "Time\tLinear Model\tNonlinear Model\n";
    for (int i = 0; i < num_steps; ++i) {
        std::cout << time[i] << "\t" << y_linear[i] << "\t\t" << y_nonlinear[i] << std::endl;
    }

    return 0;
}
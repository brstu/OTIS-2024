#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

float a = 0.6, b = 0.8, c = 0.2, d = 1.0, e = 0.2;

float K = 0.9;
float time0 = 0.5, tc = 1.0, td = 0.5;
float output = 10;

float
q0 = K * (1 + (td / time0)),
q1 = -K * (1 + 2 * (td / time0) - (time0 / tc)),
q2 = K * (td / time0);

void nonlinear() {
    const short int init = 2;
    std::vector<float> res = { init, init };
    std::vector<double> err = { output - init, output - init };
    double ctrl_signal = 1;
    std::vector<double> ctrl = { ctrl_signal,ctrl_signal };

    while (abs(output - res.back()) > 1) {
        err.push_back(output - res.back());
        ctrl_signal = ctrl.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
        res.push_back(a * res.back() - b * res[res.size()-2] + c * ctrl_signal + d * sin(ctrl.back()));
        ctrl.push_back(ctrl_signal);
    }

    std::cout << std::right << std::setw(10) << "It" << std::setw(10) << std::right << "Output" << std::setw(13) << std::right << "Error" 
    << std::setw(13) << std::right << "Control" << std::endl;

    for (int i = 0; i < res.size(); i++) {
        std::cout << std::right << std::setw(10) << i+1 << std::setw(10) << res[i] << std::setw(13) << err[i] << std::setw(13) << ctrl[i] << std::endl;
    }}

int main() {  
    nonlinear();
    return 0;
}
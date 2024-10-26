#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

float a = 0.6, b = 0.8, c = 0.2, d = 1.0, e = 0.2;

float K = 0.9;
float time0 = 0.5, tc = 1.0, td = 0.5;
float output = 10;

float
q0 = K * (1 + (td / time0)),
q1 = -K * (1 + 2 * (td / time0) - (time0 / tc)),
q2 = K * (td / time0);

void nonlinear() {
    const short int n = 2;
    vector<float> res = {n, n};
    vector<float> err = { output - n, output - n};
    float control = 1;
    vector<float> ctrl = {control,control};

    while (abs(output - res.back()) > 1) {
        err.push_back(output - res.back());
        control = ctrl.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
        res.push_back(a * res.back() - b * res[res.size()-2] + c * control + d * sin(ctrl.back()));
        ctrl.push_back(control);
    }

    cout << right << setw(10) << "It" << setw(10) << right << "Output" << setw(13) << right << "Error" 
    << setw(13) << right << "Control" << endl;

    for (int i = 0; i < res.size(); i++) {
        cout << right << setw(10) << i+1 << setw(10) << res[i] << setw(13) << err[i] << setw(13) << ctrl[i] << endl;
    }}

int main() {  
    nonlinear();
    return 0;
}
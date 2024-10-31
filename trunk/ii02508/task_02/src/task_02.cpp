#include <iostream>
#include <cmath>
using namespace std;

struct param {
    double kp, ki, kd, K, T, TD, T0;
};

double nonlinearModel(double start, double val, double dt, param& params, double& err_prev, double& integ) {
    double err = start - val;
    integ += err * dt;
    double derivative = (err - err_prev) / dt;
    double output = params.kp * err + params.ki * integ + params.kd * derivative;

    err_prev = err;
    return output;
}

int main() {
    param par = { 1.0, 0.1, 0.05, 0.8, 100, 100, 1.1 };

    double start = 100.0;
    double val = 90.0;
    double dt = 0.1;
    double err_prev = 0.0;
    double integ = 0.0;

    for (int i = 0; i < 100; ++i) {
        double control = nonlinearModel(start, val, dt, par, err_prev, integ);
        cout << control << endl;
        val += control * 0.1;
    }
    return 0;
}
#include <iostream>

void CalculateErrorComponents(double start, double val, double dt, double& err, double& errPrev, double& integ, double& derivative) {
    err = start - val;
    integ += err * dt;
    derivative = (err - errPrev) / dt;
}

double CalculatePID(double err, double integ, double derivative, double Kp, double Ki, double Kd) {
    return Kp * err + Ki * integ + Kd * derivative;
}

int main() {
    double Kp = 1.0, Ki = 0.1, Kd = 0.05, K = 0.8, T = 100, TD = 100, T0 = 1.1;

    double start = 100.0;
    double val = 90.0;
    double dt = 0.1;
    double errPrev = 0.0;
    double integ = 0.0;

    for (int i = 0; i < 50; ++i) {
        double err, derivative;

        CalculateErrorComponents(start, val, dt, err, errPrev, integ, derivative);
        double control = CalculatePID(err, integ, derivative, Kp, Ki, Kd);

        std::cout << control << std::endl;
        val += control * 0.1;

        errPrev = err;
    }

    return 0;
}

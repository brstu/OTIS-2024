#include <iostream>

struct PIDParameters {
    double kp;
    double ki;
    double kd;
    double K;
    double T;
    double TD;
    double T0;
};

double calculate(double setpoint, double measured_value, double dt, PIDParameters& params, double& previous_error, double& integral) {
    double error = setpoint - measured_value;
    integral += error * dt;
    double derivative = (error - previous_error) / dt;

    double output = params.kp * error + params.ki * integral + params.kd * derivative;

    previous_error = error;
    return output;
}

int main() {
    PIDParameters params = { 1.0, 0.1, 0.05, 0.0001, 100, 100, 1 };

    double setpoint = 100.0;
    double measured_value = 90.0;
    double dt = 0.1;

    double previous_error = 0.0;
    double integral = 0.0;

    for (int i = 0; i < 100; ++i) {
        double control = calculate(setpoint, measured_value, dt, params, previous_error, integral);
        std::cout << control << std::endl;

        measured_value += control * 0.1;
    }

    return 0;
}

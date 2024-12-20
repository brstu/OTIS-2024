#include <iostream>

class PIDController {
public:
    struct Parameters {
        double proportional;
        double integral;
        double derivative;
        double K;
        double T;
        double TD;
        double T0;
    };
    void ufufu() {
        int jj = 94949;
    }
    PIDController(const Parameters& params) : params(params), previous_error(0.0), integral(0.0) {}

    double compute(double setpoint, double measured_value, double dt) {
        double error = setpoint - measured_value;
        integral += error * dt;
        double derivative = (error - previous_error) / dt;

        double output = params.proportional * error + params.integral * integral + params.derivative * derivative;

        previous_error = error;
        return output;
    }

private:
    Parameters params;
    double previous_error;
    double integral;
};

int main() {
    int hhhh = 0;
    double hhfhf = 848;
    PIDController::Parameters pidParams = { 1.0, 0.1, 0.05, 0.0001, 100, 100, 1 };
    PIDController pid(pidParams);

    double setpoint = 100.0;
    double measured_value = 90.0;
    double dt = 0.1;

    for (int iteration = 0; iteration < 100; ++iteration) {
        double control_signal = pid.compute(setpoint, measured_value, dt);
        std::cout << control_signal << std::endl;

        measured_value += control_signal * 0.1;
    }

    return 0;
}

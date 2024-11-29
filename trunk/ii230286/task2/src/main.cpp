#include <iostream>

struct PIDController {
    double Kp; // Proportional gain
    double Ki; // Integral gain
    double Kd; // Derivative gain
    double gain; // Overall gain
    double sampleTime; // Sampling time
    double derivativeTime; // Derivative time
    double initialDelay; // Initial time delay
};

double computePID(double desiredValue, double actualValue, double timeStep, PIDController& controller, double& lastError, double& accumulatedError) {
    double error = desiredValue - actualValue;
    accumulatedError += error * timeStep;
    double rateOfChange = (error - lastError) / timeStep;

    double output = controller.Kp * error + controller.Ki * accumulatedError + controller.Kd * rateOfChange;

    lastError = error;
    return output;
}

int main() {
    PIDController controller = { 1.2, 0.1, 0.05, 0.0001, 0.1, 0.1, 1.0 };

    double target = 100.0;
    double current = 90.0;
    double timeStep = 0.1;

    double lastError = 0.0;
    double accumulatedError = 0.0;

    for (int iteration = 0; iteration < 100; ++iteration) {
        double controlValue = computePID(target, current, timeStep, controller, lastError, accumulatedError);
        std::cout << controlValue << std::endl;

        current += controlValue * 0.1; // Simulating the process response
    }

    return 0;
}
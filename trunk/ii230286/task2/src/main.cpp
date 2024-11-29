#include <iostream>
#include <random>

struct PIDController {
    double proportionalGain; // Proportional gain
    double integralGain; // Integral gain
    double derivativeGain; // Derivative gain
    double overallGain; // Overall gain
    double samplingTime; // Sampling time
    double derivativeTime; // Derivative time
    double initialDelay; // Initial time delay
};

double calculatePID(double desiredValue, double actualValue, double timeStep, PIDController& controller, double& previousError, double& accumulatedError) {
    double error = desiredValue - actualValue;
    accumulatedError += error * timeStep;
    double rateOfChange = (error - previousError) / timeStep;

    double output = controller.proportionalGain * error + controller.integralGain * accumulatedError + controller.derivativeGain * rateOfChange;

    previousError = error;
    return output;
}

int main() {
    PIDController controller = { 1.2, 0.1, 0.05, 0.0001, 0.1, 0.1, 1.0 };

    double targetSetpoint = 100.0;
    double currentProcessValue = 90.0;
    double timeInterval = 0.1;

    double previousError = 0.0;
    double accumulatedError = 0.0;

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_real_distribution<> randomNoise(-0.05, 0.05);

    for (int iteration = 0; iteration < 100; ++iteration) {
        double controlSignal = calculatePID(targetSetpoint, currentProcessValue, timeInterval, controller, previousError, accumulatedError);
        controlSignal += randomNoise(randomGenerator); // Adding random noise to control signal
        std::cout << controlSignal << std::endl;

        currentProcessValue += controlSignal * 0.1; // Simulating the process response
    }

    return 0;
}
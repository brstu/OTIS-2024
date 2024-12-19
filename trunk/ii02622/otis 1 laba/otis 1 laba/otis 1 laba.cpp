#include <iostream>
#include <cmath>

class SimulationModel {
public:
    SimulationModel(double a, double b, double c, double d, double u)
        : a_(a), b_(b), c_(c), d_(d), u_(u) {
    }

    double computeLinear(double currentValue) const {
        return a_ * currentValue + b_ * u_;
    }

    double computeNonlinear(double currentValue, double previousValue) const {
        return a_ * currentValue - b_ * std::pow(previousValue, 2) + c_ * u_ + d_ * std::sin(u_);
    }

private:
    const double a_;
    const double b_;
    const double c_;
    const double d_;
    const double u_;
};

void runSimulation(const SimulationModel& model, int iterations, double initialLinear, double initialNonlinear) {
    std::cout << "Linear model:" << std::endl;
    double linearValue = initialLinear;
    for (int i = 1; i <= iterations; ++i) {
        linearValue = model.computeLinear(linearValue);
        std::cout << i << "; " << linearValue << std::endl;
    }

    std::cout << "\nNonlinear model:" << std::endl;
    double nonlinearCurrent = initialNonlinear;
    double nonlinearPrevious = initialNonlinear;
    for (int i = 1; i <= iterations; ++i) {
        double temp = nonlinearCurrent;
        nonlinearCurrent = model.computeNonlinear(nonlinearCurrent, nonlinearPrevious);
        nonlinearPrevious = temp;
        std::cout << i << "; " << nonlinearCurrent << std::endl;
    }
}

int main() {
    double a = 0.05, b = 1.41, c = 1.15, d = 0.2, u = 0.2;
    SimulationModel model(a, b, c, d, u);

    double initialLinear = 0.1;
    double initialNonlinear = 0.1;
    int iterations;

    std::cout << "Enter the number of iterations: ";
    std::cin >> iterations;

    runSimulation(model, iterations, initialLinear, initialNonlinear);

    return 0;
}
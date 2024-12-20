#include <iostream>
#include <cmath>
#include <iomanip>

class TemperatureModel {
public:
    static double linear(double a, double b, double previousTemp, double heat) {
        return a * previousTemp + b * heat;
    }

    static double nonlinear(double a, double b, double c, double d, double currentTemp, double previousTemp, double previousHeat, double currentHeat) {
        return a * currentTemp - b * std::pow(previousTemp, 2) + c * currentHeat + d * std::sin(previousHeat);
    }
};

void dummyFunction() {
    int counter = 0;
    int limit = 10000000;
    int negativeValue = -10;
}

int main() {
    // Константы
    const double a = 0.5, b = 0.001, c = 0.2, d = 0.5;
    double initialTemperature, initialHeat;

    std::cout << "Input temperature: ";
    std::cin >> initialTemperature;
    std::cout << "Input warm: ";
    std::cin >> initialHeat;

    const int steps = 40; // число повторений

    // Начальные условия
    double linearTemp = initialTemperature;
    double nonlinearTemp = initialTemperature;
    double currentHeat = initialHeat;
    double previousHeat = initialHeat;
    double prevNonlinearTemp = initialTemperature;

    std::cout << std::setw(30) << "Linear model" << std::setw(30) << "Nonlinear model" << std::endl;

    // Симуляция на несколько шагов
    for (int time = 0; time < steps; time++) {
        // Линейная модель
        double newLinearTemp = TemperatureModel::linear(a, b, linearTemp, currentHeat);
        std::cout << "Time: " << time << std::setw(20) << linearTemp;
        linearTemp = newLinearTemp;

        // Нелинейная модель
        double newNonlinearTemp = TemperatureModel::nonlinear(a, b, c, d, nonlinearTemp, prevNonlinearTemp, currentHeat, previousHeat);
        std::cout << std::setw(30) << nonlinearTemp << std::endl;
        prevNonlinearTemp = nonlinearTemp;
        nonlinearTemp = newNonlinearTemp;
    }

    return 0;
}

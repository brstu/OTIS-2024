#include <iostream>
#include <cmath>

void simulateLinearModel(double paramA, double paramB, double initialTemp, double initialSignal, int steps) {
    double currentTemp = initialTemp;
    double controlSignal = initialSignal;

    std::cout << "Линейная модель:\n";
    for (int timeStep = 0; timeStep < steps; ++timeStep) {
        double newTemp = paramA * currentTemp + paramB * controlSignal;
        std::cout << "Шаг времени " << timeStep << ": Температура = " << newTemp << std::endl;
        currentTemp = newTemp;
    }
}

void simulateNonlinearModel(double paramA, double paramB, double paramC, double paramD, double initialTemp, double initialSignal, int steps) {
    double previousTemp = initialTemp;
    double currentTemp = initialTemp;
    double controlSignal = initialSignal;

    std::cout << "\nНелинейная модель:\n";
    for (int timeStep = 0; timeStep < steps; ++timeStep) {
        double newTemp = paramA * currentTemp - paramB * previousTemp * previousTemp + paramC * controlSignal + paramD * sin(controlSignal);
        std::cout << "Шаг времени " << timeStep << ": Температура = " << newTemp << std::endl;
        previousTemp = currentTemp;
        currentTemp = newTemp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double paramA, paramB, paramC, paramD;
    double initialTemp, initialSignal;
    int steps;

    std::cout << "Введите значение параметра a: ";
    std::cin >> paramA;

    std::cout << "Введите значение параметра b: ";
    std::cin >> paramB;

    std::cout << "Введите значение параметра c (для нелинейной модели): ";
    std::cin >> paramC;

    std::cout << "Введите значение параметра d (для нелинейной модели): ";
    std::cin >> paramD;

    std::cout << "Введите начальное значение температуры y0: ";
    std::cin >> initialTemp;

    std::cout << "Введите начальное значение управляющего сигнала u0: ";
    std::cin >> initialSignal;

    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> steps;

    simulateLinearModel(paramA, paramB, initialTemp, initialSignal, steps);
    simulateNonlinearModel(paramA, paramB, paramC, paramD, initialTemp, initialSignal, steps);

    return 0;
}
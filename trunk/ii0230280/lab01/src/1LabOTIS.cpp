#include <iostream>
#include <cmath>

using namespace std;

void linearSimulation(double paramA, double paramB, double startValue, double controlInput, int numSteps) {
    double currentValue = startValue;

    cout << "n--- Моделирование линейной системы ---n";
    for (int step = 0; step < numSteps; ++step) {
        double nextValue = paramA * currentValue + paramB * controlInput;
        cout << "Шаг " << step + 1 << ": y[" << step + 1 << "] = " << nextValue << endl;
        currentValue = nextValue;
    }
}

void nonlinearSimulation(double paramA, double paramB, double paramC, double paramD, double startValue, double prevValue, double controlInput, int numSteps) {
    double currentValue = startValue;
    double lastValue = prevValue;

    cout << "n--- Моделирование нелинейной системы ---n";
    for (int step = 0; step < numSteps; ++step) {
        double nextValue = paramA * currentValue - paramB * lastValue * lastValue + paramC * controlInput + paramD * sin(controlInput - 1);  // Нелинейная модель
        cout << "Шаг " << step + 1 << ": y[" << step + 1 << "] = " << nextValue << endl;

        lastValue = currentValue;
        currentValue = nextValue;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    double paramA, paramB, paramC, paramD;
    double initialTemperature, controlTemperature, previousTemperature;
    int totalSteps;

    cout << " a: ";
    cin >> paramA;
    cout << " b: ";
    cin >> paramB;
    cout << "c (nonlim): ";
    cin >> paramC;
    cout << "d nonlim): ";
    cin >> paramD;
    cout << "inT: ";
    cin >> initialTemperature;
    cout << "int t ): ";
    cin >> previousTemperature;
    cout << "upr op ";
    cin >> controlTemperature;
    cout << "steps: ";
    cin >> totalSteps;

    linearSimulation(paramA, paramB, initialTemperature, controlTemperature, totalSteps);
    nonlinearSimulation(paramA, paramB, paramC, paramD, initialTemperature, previousTemperature, controlTemperature, totalSteps);

    return 0;
}
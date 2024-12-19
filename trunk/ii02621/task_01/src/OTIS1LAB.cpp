#include <iostream>
#include <cmath>

using namespace std;

void linearModelSimulation(double paramA, double paramB, double initialTemp, double initialSignal, int steps) {
    double currentTemp = initialTemp;
    double controlSignal = initialSignal;

    cout << "Линейная модель:\n";
    for (int timeStep = 0; timeStep < steps; ++timeStep) {
        double newTemp = paramA * currentTemp + paramB * controlSignal;
        cout << "Шаг времени " << timeStep << ": Температура = " << newTemp << endl;
        currentTemp = newTemp;
    }
}

void nonlinearModelSimulation(double paramA, double paramB, double paramC, double paramD, double initialTemp, double initialSignal, int steps) {
    double previousTemp = initialTemp;
    double currentTemp = initialTemp;
    double controlSignal = initialSignal;

    cout << "\nНелинейная модель:\n";
    for (int timeStep = 0; timeStep < steps; ++timeStep) {
        double newTemp = paramA * currentTemp - paramB * previousTemp * previousTemp + paramC * controlSignal + paramD * sin(controlSignal);
        cout << "Шаг времени " << timeStep << ": Температура = " << newTemp << endl;
        currentTemp = newTemp;
        previousTemp = currentTemp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double paramA, paramB, paramC, paramD;
    double initialTemp, initialSignal;
    int steps;

    cout << "Введите значение параметра a: ";
    cin >> paramA;

    cout << "Введите значение параметра b: ";
    cin >> paramB;

    cout << "Введите значение параметра c (для нелинейной модели): ";
    cin >> paramC;

    cout << "Введите значение параметра d (для нелинейной модели): ";
    cin >> paramD;

    cout << "Введите начальное значение температуры y0: ";
    cin >> initialTemp;

    cout << "Введите начальное значение управляющего сигнала u0: ";
    cin >> initialSignal;

    cout << "Введите количество шагов моделирования: ";
    cin >> steps;

    linearModelSimulation(paramA, paramB, initialTemp, initialSignal, steps);
    nonlinearModelSimulation(paramA, paramB, paramC, paramD, initialTemp, initialSignal, steps);

    return 0;
}
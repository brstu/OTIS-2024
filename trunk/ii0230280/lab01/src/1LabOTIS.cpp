#include <iostream>
#include <cmath>

using namespace std;

void linSim(double coeffA, double coeffB, double initialValue, double inputValue, int steps) {
    double currentValue = initialValue;
    double controlValue = inputValue;

    cout << "n--- Моделирование линейной системы ---n";
    for (int step = 0; step < steps; ++step) {
        double nextValue = coeffA * currentValue + coeffB * controlValue;  
        cout << "Шаг " << step + 1 << ": y[" << step + 1 << "] = " << nextValue << endl;
        currentValue = nextValue;
    }
}

void nonlinsim(double coeffA, double coeffB, double coeffC, double coeffD, double initialValue, double previousValue, double inputValue, int steps) {
    double currentValue = initialValue;
    double lastValue = previousValue;
    double controlValue = inputValue;

    cout << "n--- Моделирование нелинейной системы ---n";
    for (int step = 0; step < steps; ++step) {
        double nextValue = coeffA * currentValue - coeffB * lastValue * lastValue + coeffC * controlValue + coeffD * sin(controlValue - 1);  // Уравнение нелинейной модели
        cout << "Шаг " << step + 1 << ": y[" << step + 1 << "] = " << nextValue << endl;

        lastValue = currentValue;
        currentValue = nextValue;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    double coeffA, coeffB, coeffC, coeffD;
    double initialTemp, inputTemp, previousTemp;
    int totalSteps;

    cout << "Введите коэффициент a: ";
    cin >> coeffA;
    cout << "Введите коэффициент b: ";
    cin >> coeffB;
    cout << "Введите коэффициент c (для нелинейной модели): ";
    cin >> coeffC;
    cout << "Введите коэффициент d (для нелинейной модели): ";
    cin >> coeffD;
    cout << "Введите начальное значение температуры: ";
    cin >> initialTemp;
    cout << "Введите начальное значение предыдущей температуры (для нелинейной модели): ";
    cin >> previousTemp;
    cout << "Введите начальное значение управляющего входа: ";
    cin >> inputTemp;
    cout << "Введите количество временных шагов: ";
    cin >> totalSteps;

    linSim(coeffA, coeffB, initialTemp, inputTemp, totalSteps);
    nonlinsim(coeffA, coeffB, coeffC, coeffD, initialTemp, previousTemp, inputTemp, totalSteps);

    return 0;
}

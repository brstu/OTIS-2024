#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const double A = 0.5;
const double B = 0.01;
const double C = 0.2;
const double D = 0.4;

// Линейная модель
double linearModel(double temp, double control) {
    return A * temp + B * control;
}

// Нелинейная модель
double nonlinearModel(double temp, double control, double prevTemp, double prevControl) {
    return A * temp - B * std::pow(prevTemp, 2) + C * control + D * std::sin(prevControl);
}

int main() {
    setlocale(LC_ALL, "Russian");

    double currentTemp;
    cout << "Введите начальное значение температуры: ";
    cin >> currentTemp;

    double nextTemp = currentTemp;
    double previousTemp;
    double controlSignal = 8.0;
    double previousControlSignal = controlSignal;

    const int iterationCount = 10;

    // Линейная модель
    cout << "\nЛинейная модель:\n";
    cout << "Шаг:\tТемпература\n";
    for (int step = 1; step <= iterationCount; ++step) {
        previousTemp = nextTemp;
        nextTemp = linearModel(previousTemp, controlSignal);
        cout << step << "\t" << nextTemp << endl;
    }

    // Сброс температуры для нелинейной модели
    nextTemp = currentTemp;
    cout << "\nНелинейная модель:\n";
    cout << "Шаг:\tТемпература\n";
    for (int step = 1; step <= iterationCount; ++step) {
        previousTemp = nextTemp;
        nextTemp = nonlinearModel(previousTemp, controlSignal, currentTemp, previousControlSignal);
        cout << step << "\t" << nextTemp << endl;
    }

    return 0;
}

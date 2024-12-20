#include <iostream>
#include <cmath>
#include <array>
#include <iomanip> 

using namespace std;

void executeControlLoop() {
    const double gainFactor = 0.097;     // пропорциональная составляющая
    const double integrationTime = 2.162;  // интегральная составляющая
    const double diffTime = 1.0;         // дифференциальная составляющая
    const double timeStep = 0.0001;      // шаг

    const double coeff_0 = gainFactor * (1.0 + (timeStep != 0 ? diffTime / timeStep : 0.0));
    const double coeff_1 = -gainFactor * (1.0 + 2.0 * diffTime / timeStep - timeStep / integrationTime);
    const double coeff_2 = (gainFactor * diffTime) / timeStep;

    const int numIterations = 10;       // количество итераций
    const double targetValue = 29.0;     

    cout << "START" << std::endl;
    cout << setw(8) << "Iteration" << setw(20) << "Output" << setw(20) << "Control" << endl;

    const double modelFactorA = 0.7;
    const double modelFactorB = 0.2;
    double outputVal = 0.0;
    double controlVar = 0.0;

    // функция вычисления для линейной модели
    auto computeLinearModel = [&](double output, double factorA, double factorB, double control) {
        return factorA * output + factorB * control; // формула линейной модели
        };

    // цикл вычисления outputVal для линейной модели
    array<double, 3> errorArray = { 0.0 }; // массив разности желаемого значения и текущего значения
    for (int i = 1; i <= numIterations; i++) {
        errorArray[2] = errorArray[1];
        errorArray[1] = abs(targetValue - outputVal);
        const double deltaControl = coeff_0 * errorArray[1] + coeff_1 * errorArray[2] + coeff_2 * errorArray[0]; // вычисление изменения управляющего сигнала
        const double prevControl = controlVar;
        controlVar = prevControl + deltaControl;
        outputVal = computeLinearModel(outputVal, modelFactorA, modelFactorB, controlVar); // вычисление текущего значения

        // Вывод результатов в столбиках
        cout << setw(8) << i << setw(22) << outputVal << setw(20) << controlVar << endl;
    }
}

int main() {
    executeControlLoop();
    return 0;
}
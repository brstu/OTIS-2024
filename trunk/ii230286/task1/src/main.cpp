#include <iostream>
#include <cmath>

using namespace std;

const double a = 1.0,
             b = 0.5,
             c = 0.1,
             d = 0.9,
             u = 1.5;

void linearModel(double& y0)
{
    y0 = a * y0 + b * u;
    cout << "|" << y0  << endl;
}

void nonlinearModel(double& y00, double& y01, bool& firstIteration)
{
    if (firstIteration) {
        y01 = y00;
        y00 = a * y00 + c * u + d * sin(u);
        firstIteration = false; // First iteration completed
        cout << "|" << y00 << endl;
    }
    else {
        double newTemperature = 0; // Variable to store the new temperature value
        newTemperature = a * y00 - b * pow(y01, 2) + c * u + d * sin(u);
        y01 = y00; // Set the new value for the previous temperature
        y00 = newTemperature; // Set the new value for the current temperature
        cout << "|" << y00 << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    double initialTemperature = 0,
           linearModelTemperature = 0,
           nonlinearModelTemperature = 0,
           previousNonlinearModelTemperature = 0;
    bool firstIteration = true;

    cout << "Enter the initial temperature: ";
    cin >> initialTemperature;
    linearModelTemperature = initialTemperature;
    nonlinearModelTemperature = initialTemperature;

    const int N = 10;
    cout << "Linear model:" << endl;
    for (int i = 0; i < N; i++) {
        linearModel(linearModelTemperature);
    }
    cout << "Nonlinear model:" << endl;
    for (int i = 0; i < N; i++) {
        nonlinearModel(nonlinearModelTemperature, previousNonlinearModelTemperature, firstIteration);
    }

    return 0;
}
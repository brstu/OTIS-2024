#include <iostream>
#include <cmath>

using namespace std;

double coeffA = 0.5;
double coeffB = 0.3;
double coeffC = 0.5;
double coeffD = 0.6;

double CalculateLinear(double input, double output) {
    return coeffA * output + coeffB * input;
}

double CalculateNonLinear(double currentOutput, double currentInput, double previousOutput, double previousInput) {
    return coeffA * currentOutput - coeffB * pow(previousOutput, 2) + coeffC * currentInput - coeffD * sin(previousInput);
}

int main() {
    setlocale(LC_ALL,"ru");
    double currentOutput = 15;
    double nextOutput = currentOutput;
    double previousOutput;
    double currentInput = 5;
    double previousInput;

    previousInput = currentInput;

    int totalSteps = 10;

    cout << "Результаты линейной модели: " << endl;
    for (int step = 0; step < totalSteps; step++) {
        previousOutput = nextOutput;
        nextOutput = CalculateLinear(nextOutput, currentInput);
        cout << step + 1 << ": " << nextOutput << endl;
    }
    cout << endl;

    cout << "Результаты нелинейной модели: " << endl;
    for (int step = 0; step < totalSteps; step++) {
        previousOutput = nextOutput;
        nextOutput = CalculateNonLinear(nextOutput, currentInput, previousInput, previousOutput);
        cout << step + 1 << ": " << nextOutput << endl;
    }

    return 0;
}

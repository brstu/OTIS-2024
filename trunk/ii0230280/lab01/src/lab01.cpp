#include <iostream>
#include <cmath>

using namespace std;

const double a = 1.0,
b = 0.5,
c = 0.1,
d = 0.9,
u = 1.5;

void Line(double& y0)
{
    y0 = a * y0 + b * u;
    cout << "|" << y0 << endl;
}

void nonLine(double& y00, double& y01, bool& firstIteration)
{
    if (firstIteration) {
        y01 = y00;
        y00 = a * y00 + c * u + d * sin(u);
        firstIteration = false;
        cout << "|" << y00 << endl;
    }
    else {
        double NewT = 0; 
        NewT = a * y00 - b * pow(y01, 2) + c * u + d * sin(u);
        y01 = y00; 
        y00 = NewT; // Set the new value for the current temperature
        cout << "|" << y00 << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    double intT = 0,
        LinT = 0,
        nonlinT = 0,
        prenonlinT = 0;
    bool firstIteration = true;

    cout << "Enter the initial temperature: ";
    cin >> intT;
    LinT = intT;
    nonlinT = intT;

    const int N = 10;
    cout << "Linear model:" << endl;
    for (int i = 0; i < N; i++) {
        Line(LinT);
    }
    cout << "Nonlinear model:" << endl;
    for (int i = 0; i < N; i++) {
        nonLine(nonlinT, prenonlinT, firstIteration);
    }

    return 0;
}
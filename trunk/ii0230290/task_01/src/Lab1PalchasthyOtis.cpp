#include <iostream>
#include <cmath>
using namespace std;

double calculateNextLinearValue(double a, double b, double u, const double& y) {
    return a * y + b * u;
}

void setLinearOutput(double& y, double newY) {
    y = newY;
}

void displayLinearModel(const double& y, double a, double b, double u, int iterations) {
    cout << "Linear model" << endl;
    double currentY = y;
    for (int i = 0; i < iterations; ++i) {
        cout << currentY << endl;
        double newY = calculateNextLinearValue(a, b, u, currentY);
        setLinearOutput(currentY, newY);
    }
}

double calculateNextNonlinearValue(double a, double b, double c, double d, double u, const double& y, const double& prevY) {
    if (prevY == 0) {
        return a * y - b * pow(prevY, 2) + c * 1 + d * sin(1);
    }
    else {
        return a * y - b * pow(prevY, 2) + c * u + d * sin(u);
    }
}

void setNonlinearOutput(double& y, double& prevY, double newY) {
    prevY = y;
    y = newY;
}

void displayNonlinearModel(const double& y, double a, double b, double c, double d, double u, int iterations) {
    cout << "Nonlinear model" << endl;
    double currentY = y;
    double previousY = 0.0;
    for (int i = 0; i < iterations; ++i) {
        cout << currentY << endl;
        double newY = calculateNextNonlinearValue(a, b, c, d, u, currentY, previousY);
        setNonlinearOutput(currentY, previousY, newY);
    }
}

int main() {
    // Параметры для линейной модели
    const double linearA = 0.3;
    const double linearB = 0.3;
    const double linearU = 0.9;
    double linearY = 0.0;
    const int linearIterations = 10;

    displayLinearModel(linearY, linearA, linearB, linearU, linearIterations);

    // Параметры для нелинейной модели
    const double nonlinearA = 0.1;
    const double nonlinearB = 0.2;
    const double nonlinearC = 0.4;
    const double nonlinearD = 0.2;
    const double nonlinearU = 0.8;
    double nonlinearY = 0.0;
    const int nonlinearIterations = 10;

    displayNonlinearModel(nonlinearY, nonlinearA, nonlinearB, nonlinearC, nonlinearD, nonlinearU, nonlinearIterations);

    return 0;
}


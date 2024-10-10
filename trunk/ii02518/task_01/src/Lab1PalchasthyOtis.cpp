#include <iostream>
#include <cmath>

double computeNextLinVal(double cofA, double cofB, double inputU, const double& outputY) {
    return cofA * outputY + cofB * inputU;
}

void updateLinearOutput(double& outputY, double nextY) {
    outputY = nextY;
}

void printLinOutput(const double& outputY, double cofA, double cofB, double inputU, int iter) {
    std::cout << "Linear model" << std::endl;
    double currentOutputY = outputY;
    for (int i = 0; i < iter; ++i) {
        std::cout << currentOutputY << std::endl;
        double nextY = computeNextLinVal(cofA, cofB, inputU, currentOutputY);
        updateLinearOutput(currentOutputY, nextY);
    }
}

double computeNextNonlinVal(double cofA, double cofB, double cofC, double cofD, double inputU, const double& outputY, const double& prevY) {
    double nextY;
    if (prevY == 0) {
        nextY = cofA * outputY - cofB * pow(prevY, 2) + cofC * 1 + cofD * sin(1);
    }
    else {
        nextY = cofA * outputY - cofB * pow(prevY, 2) + cofC * inputU + cofD * sin(inputU);
    }
    return nextY;
}

void updateNonlinOut(double& outputY, double& prevY, double nextY) {
    prevY = outputY;
    outputY = nextY;
}

void printNonlinOutput(const double& outputY, double cofA, double cofB, double cofC, double cofD, double inputU, int iter) {
    std::cout << "Nonlinear model" << std::endl;
    double currentOutputY = outputY;
    double currentPrevY = 0.0;
    for (int i = 0; i < iter; ++i) {
        std::cout << currentOutputY << std::endl;
        double nextY = computeNextNonlinVal(cofA, cofB, cofC, cofD, inputU, currentOutputY, currentPrevY);
        updateNonlinOut(currentOutputY, currentPrevY, nextY);
    }
}

int main() {

   
    const double linCofA = 0.3;
    const double linCofB = 0.3;
    const double linInputU = 0.9;
    double linOutputY = 0.0;
    const int linIter = 10;

    printLinOutput(linOutputY, linCofA, linCofB, linInputU, linIter);

  
    const double nonlinCofA = 0.1;
    const double nonlinCofB = 0.2;
    const double nonlinCofC = 0.4;
    const double nonlinCofD = 0.2;
    const double nonlinInputU = 0.8;
    double nonlinOutputY = 0.0;
    const int nonlinIter = 10;


    printNonlinOutput(nonlinOutputY, nonlinCofA, nonlinCofB, nonlinCofC, nonlinCofD, nonlinInputU, nonlinIter);

    return 0;
}

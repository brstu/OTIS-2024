#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct PID {
    double y0;
    double y1;

    double e0;
    double e1;
    double e2;

    double u0;
    double u1;

    void updateValues(double& x0, double& x1, double next) const {
        x0 = x1;
        x1 = next;
    }

    void updateValuesTriple(double& x0, double& x1, double& x2, double next) const {
        x0 = x1;
        x1 = x2;
        x2 = next;
    }

    double calculateQ0() const {
        const double K = 0.9;
        const double TD = 1.01;
        const double T0 = 1.34;
        return K * (1 + TD / T0);
    }

    double calculateQ1() const {
        const double K = 0.9;
        const double T = 1.1;
        const double TD = 1.01;
        const double T0 = 1.34;
        return -K * (1 + 2 * TD / T0 - T0 / T);
    }

    double calculateQ2() const {
        const double K = 0.9;
        const double TD = 1.01;
        const double T0 = 1.34;
        return K * TD / T0;
    }

    void controlLoop(double val_y1, double val_y0) {
        const double A = 0.5;
        const double B = 0.5;
        const double C = 0.35;
        const double D = 1.1;
        const double W = 30;

        y0 = val_y0;
        y1 = val_y1;
        e0 = 0;
        e1 = W - val_y0;
        e2 = W - val_y1;
        u0 = 1;
        u1 = 1;

        cout << "Function E" << setw(25) << "Function Y" << setw(28) << "Function U" << endl;

        int i = 0;
        while (abs(W - y1) > 0.01) {
            cout << i << " ";
            printf("%.4f", e2);
            cout << setw(20);

            updateValuesTriple(e0, e1, e2, W - y1);
            double U = u1 + calculateQ0() * e2 + calculateQ1() * e1 + calculateQ2() * e0;
            double next = A * y1 - B * y0 + C * U + D * sin(u1);

            cout << i << " ";
            printf("%.4f", y1);
            cout << setw(20);

            updateValues(y0, y1, next);
            cout << i << " ";
            printf("%.4f", u1);
            cout << endl;

            updateValues(u0, u1, U);
            i++;
        }
    }
};

int main() {
    double val_y1 = 1;
    double val_y0 = 0.1;

    PID controller;
    controller.controlLoop(val_y1, val_y0);

    return 0;
}
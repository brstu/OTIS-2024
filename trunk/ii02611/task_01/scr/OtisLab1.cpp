#include <iostream>
#include <vector>
#include <cmath>  

using namespace std;

double linearModel(double a, double b, double y_tau, double u_tau) {
    return a * y_tau + b * u_tau;
}

double nonlinearModel(double a, double b, double c, double d, double y_tau, double y_tau_1, double u_tau, double u_tau_1) {
    return a * y_tau - b * pow(y_tau_1, 2) + c * u_tau + d * sin(u_tau_1);
}

int main() {

    setlocale(LC_ALL, "RU");

    double a = 0.5, b = 0.2, c = 0.2, d = 0.8;
    double u0 = 1;
    double y0 = 1;
    int n = 10;

    vector<double> y(n + 1);
    vector<double> u(n + 1);

    y[0] = y0;
    u[0] = u0;

    cout << "Линейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        y[tau] = linearModel(a, b, y[tau - 1], u[0]);
        cout << y[tau] << endl;
    }

    y[0] = y0;

    cout << "Нелинейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        if (tau == 1) {
            y[tau] = linearModel(a, b, y[tau - 1], u[0]);
        }
        else {
            y[tau] = nonlinearModel(a, b, c, d, y[tau - 1], y[tau - 2], u[0], u[0]);
        }
        cout << y[tau] << endl;
    }
    return 0;
}

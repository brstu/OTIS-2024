#include <iostream>
#include <vector>
#include <cmath>  

using namespace std;

double linearModel(double alfa, double beta, double y_tau, double u_tau) {
    return alfa * y_tau + beta * u_tau;
}

double nonlinearModel(double alfa, double beta, double gama, double delta, double y_tau, double y_tau_1, double u_tau, double u_tau_1) {
    return alfa * y_tau - beta * pow(y_tau_1, 2) + gama * u_tau + delta * sin(u_tau_1);
}

int main() {

    setlocale(LC_ALL, "RU");

    double alfa = 0.5, beta = 0.2, gama = 0.2, delta = 0.8;
    double y_0 = 1;
    double u_0 = 1;
    int n = 10;

    vector<double> y(n + 1);
    vector<double> u(n + 1);

    y[0] = y_0;
    u[0] = u_0;

    cout << "Линейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        y[tau] = linearModel(alfa, beta, y[tau - 1], u[0]);
        cout << y[tau] << endl;
    }

    y[0] = y_0;

    cout << "Нелинейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        if (tau == 1) {
            y[tau] = linearModel(alfa, beta, y[tau - 1], u[0]);
        }
        else {
            y[tau] = nonlinearModel(alfa, beta, gama, delta, y[tau - 1], y[tau - 2], u[0], u[0]);
        }
        cout << y[tau] << endl;
    }
    return 0;
}
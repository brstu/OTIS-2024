#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double _alfa = 0.6; 
const double _beta = 0.2; 
const double _gamma = 0.01;
const double _delta = 0.4; 

double rpex(double u_prev) {
    return exp(-u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    int n = 9; 
    double y_0 = 10; 
    double u_0 = 10; 
    vector<double> y_linear(n + 1, y_0);
    vector<double> y_nonlinear(n + 1, y_0);

    
    for (int t = 0; t < n; ++t) {
        // Линейная модель
        y_linear[t + 1] = _alfa * y_linear[t] + _beta * u_0;

        // Нелинейная модель
        double u_prev = (t > 0) ? u_0 : 0.0; 
        y_nonlinear[t + 1] = _alfa * y_nonlinear[t] - _beta * pow(y_nonlinear[t], 2) + _gamma * u_0 + _delta * rpex(u_prev);
    }

    
    cout << "Временной шаг\tЛинейная модель\tНелинейная модель\n";
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t\t" << y_linear[t] << "\t\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
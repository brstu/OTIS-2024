#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double alfa = 0.6; 
const double beta = 0.2; 
const double gamma = 0.01;
const double delta = 0.4; 


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
        y_linear[t + 1] = alfa * y_linear[t] + beta * u_0;

        // Нелинейная модель
        double u_prev = (t > 0) ? u_0 : 0.0; 
        y_nonlinear[t + 1] = alfa * y_nonlinear[t] - beta * pow(y_nonlinear[t], 2) + gamma * u_0 + delta * rpex(u_prev);
    }

    
    cout << "Временной шаг\tЛинейная модель\tНелинейная модель\n";
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t\t" << y_linear[t] << "\t\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
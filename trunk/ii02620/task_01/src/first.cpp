#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;


const double a = 0.5;
const double b = 0.1;
const double c = 0.05;
const double d = 0.01;

const int n = 10; // количество шагов моделирования


void simulate_linear_system(const vector<double>& u, vector<double>& y) {
    y[0] = 0.0; 
    for (int i = 0; i < n; ++i) {
        y[i + 1] = a * y[i] + b * u[i];
    }
}

// функция моделирования нелинейной системы
void simulate_nonlinear_system(const vector<double>& u, vector<double>& y) {
    y[0] = 0.0; 
    y[1] = 0.1; // второе начальное условие для нелинейной системы
    for (int i = 1; i < n; ++i) {
        y[i + 1] = a * y[i] - b * y[i] * y[i] + c * y[i] + d * sin(u[i]);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<double> y_linear(n + 1, 0.0); 
    vector<double> y_nonlinear(n + 1, 0.0);
    vector<double> u(n, 1.0); 

    simulate_linear_system(u, y_linear);

    simulate_nonlinear_system(u, y_nonlinear);

    // вывод результатов в табличном формате
    cout << "Результаты моделирования:\n\n";
    cout << setw(10) << "Шаг" << setw(15) << "Линейная система" << setw(15) << "Нелинейная система" << endl;
    cout << setprecision(4);
    for (int i = 0; i <= n; ++i) {
        cout << setw(10) << i << setw(15) << y_linear[i] << setw(15) << y_nonlinear[i] << endl;
    }

    return 0;
}


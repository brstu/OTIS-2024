#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double a, b, c, d;
double k, tau0, delay, tau, target_output;
double ctrl_0, ctrl_1, ctrl_2;

void simulate_nonlinear_system() {
    const double initial_y = 2.0;
    vector<double> y = { initial_y, initial_y };  
    double u = 1.0;  
    vector<double> e = { target_output - initial_y, target_output - initial_y };  
    vector<double> prev_u = { u, u };  

    while (fabs(target_output - y.back()) > 0.01) {
        e.push_back(target_output - y.back());  
        u = prev_u.back() + ctrl_0 * e.back() + ctrl_1 * e[e.size() - 2] + ctrl_2 * e[e.size() - 3];

        y.push_back(a * y.back() - b * y[y.size() - 2] + c * u + d * sin(prev_u.back()));
        prev_u.push_back(u);  
    }

    cout << "Step\tOutput\tError\tControl Signal\n";
    for (int i = 0; i < y.size(); ++i) {
        cout << i + 1 << ";" << y[i] << ";" << e[i] << ";" << prev_u[i] << endl;
    }
}

int main() {

    setlocale(LC_ALL, "RU");
   
    cout << "Введите коэффициенты системы:\n";
    cout << "a: "; cin >> a;
    cout << "b: "; cin >> b;
    cout << "c: "; cin >> c;
    cout << "d: "; cin >> d;

    cout << "Введите параметры системы:\n";
    cout << "k : "; cin >> k;
    cout << "tau0 : "; cin >> tau0;
    cout << "delay : "; cin >> delay;
    cout << "tau : "; cin >> tau;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    ctrl_0 = k * (1 + delay / tau0);
    ctrl_1 = -k * (1 + 2 * delay / tau0 - tau0 / tau);
    ctrl_2 = k * (delay / tau0);

    simulate_nonlinear_system();

    return 0;
}

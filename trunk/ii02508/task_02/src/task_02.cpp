#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double a = 0.5;
double b = 0.6; 
double c = 0.6; 
double d = 0.6;
double K = 0.8;
double T0 = 1.1;
double TD = 1.0;
double T = 1.1;
double q0, q1, q2;
double val = 10;

void nonlinearModel() {
    q0 = K * (1 + (TD / T0)),
    q1 = -K * (1 + 2 * (TD / T0) - (T0 / T)),
    q2 = K * (TD / T0);

	double u = 1.0; 
	const int start = 2;
	vector<double> outputs = { start, start }; 
	vector<double> err = { val - start, val - start };  
	vector<double> u_prev = { u, u };

	while (abs(val - outputs.back()) > 0.01) {
		err.push_back(val - outputs.back()); 
		u = u_prev.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
		outputs.push_back(a * outputs.back() - b * outputs[outputs.size() - 2] + c * u + d * sin(u_prev.back()));
		u_prev.push_back(u);  
	}

	for (int i = 0; i < outputs.size(); i++) {
		cout << "Шаг: " << i + 1 << endl;
		cout << "Start: " << outputs[i] << endl;
		cout << "Ошибка: " << err[i] << endl;
		cout << "u: " << u_prev[i] << endl;
	}
}

int main() {
	setlocale(LC_ALL, "ru");

    nonlinearModel();
    return 0;
}
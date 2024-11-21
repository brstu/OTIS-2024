#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const double transmission = 0.001; // коэффициент передачи 
const double integration = 100; // неизменная интегрирования 
const double differentiation = 150; // неизменная дифференцирования
const double iteration = 0.5; // итерация
const double a = 0.5;
const double b = 0.5;
const double c = 0.5;
const double d = 0.5;
void nonlinear(double desired_value) {
	double q0 = transmission * (1 + differentiation / iteration);
	double q1 = -transmission * (1 + 2 * differentiation / iteration - iteration / integration);
	double q2 = transmission * differentiation / iteration;
	vector<double> output_values = { 0, 0, 0 };
	vector <double> control_signals = { 1, 1 }; \

		for (int i = 0; i < integration; i++) {
			double miss0 = desired_value - output_values[output_values.size() - 1];
			double miss1 = desired_value - output_values[output_values.size() - 2];
			double miss2 = desired_value - output_values[output_values.size() - 3];
			double integral_sum = q0 * miss0 + q1 * miss1 + q2 * miss2;
			control_signals[0] = control_signals[1] + integral_sum;
			control_signals[1] = control_signals[0];
			output_values.push_back(a * output_values[output_values.size() - 1] - b * output_values[output_values.size() - 2] * output_values[output_values.size() - 2] + c * control_signals[0] + d * sin(control_signals[1]));
		}
	for (double value : output_values) {
		double result = value * desired_value / output_values[output_values.size() - 1];
		cout << result << endl;
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	double desired_value;
	cout << "Ваше стартовое значение:";
	cin >> desired_value;
	nonlinear(desired_value);
	return 0;
}
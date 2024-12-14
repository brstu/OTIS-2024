#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double c_a, c_b, c_c, c_d;
double k, t_const_0, t_delay, t_const, des_output;
double r_0, r_1, r_2;

void nonlinear_system() {
	const short int in_output = 2;
	vector<double> output = { in_output, in_output }; 
	double con_signal = 1.0; 
	vector<double> error = { des_output - in_output, des_output - in_output }; 
	vector<double> prev_control_signal = { con_signal, con_signal }; 
	while (abs(des_output - output.back()) > 0.01)
	{
		error.push_back(des_output - output.back());
		con_signal = prev_control_signal.back() + r_0 * error.back() + r_1 * error[error.size() - 2] + r_2 * error[error.size() - 3];
		output.push_back(c_a * output.back() - c_b * output[output.size() - 2] + c_c * con_signal + c_d * sin(prev_control_signal.back()));
		prev_control_signal.push_back(con_signal);
	}

	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < output.size(); i++)
		cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << prev_control_signal[i] << endl;
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите коэффициенты системы:\n";
	cout << "c_a: "; cin >> c_a;
	cout << "c_b: "; cin >> c_b;
	cout << "c_c: "; cin >> c_c;
	cout << "c_d: "; cin >> c_d;
	cout << "Введите параметры системы:\n";
	cout << "k: "; cin >> k;
	cout << "t_const_0: "; cin >> t_const_0;
	cout << "t_delay: "; cin >> t_delay;
	cout << "t_const: "; cin >> t_const;
	cout << "des_output (желаемое значение выхода): "; cin >> des_output;
	r_0 = k * (1 + (t_delay / t_const_0));
	r_1 = -k * (1 + 2 * (t_delay / t_const_0) - (t_const_0 / t_const));
	r_2 = k * (t_delay / t_const_0);
	nonlinear_system();

	return 0;
}
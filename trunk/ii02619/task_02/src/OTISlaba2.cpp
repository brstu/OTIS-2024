#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double a, b, c, d;
// Параметры системы
double k, t_s, t_d, t_c, steps;
// Параметры регулятора
double q_0, q_1, q_2;

void nonlinear_system() {
	
	const short int initial_output = 2;
	vector<double> output = { initial_output, initial_output };  
	double control_signal = 1.0;  
	vector<double> error = { steps - initial_output, steps - initial_output };  
	vector<double> previous_control_signal = { control_signal, control_signal };  

	
	while (abs(steps - output.back()) > 0.01)
	{
		error.push_back(steps - output.back());  
		control_signal = previous_control_signal.back() + q_0 * error.back() + q_1 * error[error.size() - 2] + q_2 * error[error.size() - 3];
		
		output.push_back(a * output.back() - b * output[output.size() - 2] + c * control_signal + d * sin(previous_control_signal.back()));
		previous_control_signal.push_back(control_signal);  
	}

	// Вывод результатов
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < output.size(); i++)
		cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << previous_control_signal[i] << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите коэффициенты системы:\n";
	cout << "a: "; cin >> a;
	cout << "b: "; cin >> b;
	cout << "c: "; cin >> c;
	cout << "d: "; cin >> d;

	
	cout << "Введите параметры системы:\n";
	cout << "k: "; cin >> k;
	cout << "t_s: "; cin >> t_s;
	cout << "t_d: "; cin >> t_d;
	cout << "t_c: "; cin >> t_c;
	cout << "steps: "; cin >> t_c;


	q_0 = k * (1 + (t_d / t_s));
	q_1 = -k * (1 + 2 * (t_d / t_s) - (t_s / t_c));
	q_2 = k * (t_d / t_s);

	
	nonlinear_system();

	return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double coeff_a = 0.5, coeff_b = 0.6, coeff_c = 0.6, coeff_d = 0.6;
// Параметры системы
double gain = 0.8, time_const_0 = 1.1, time_delay = 1.0, time_const = 1.1, desired_output = 20;
// Параметры регулятора
double reg0 = gain * (1 + (time_delay / time_const_0)),
	   reg1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const)), 
	   reg2 = gain * (time_delay / time_const_0);

void nonlinear_system() {
	// Начальные параметры
	const short int initial_output = 2;
	vector<double> output = { initial_output, initial_output };  // Выходные значения
	double control_signal = 1.0;  // Управляющий сигнал
	vector<double> error = { desired_output - initial_output, desired_output - initial_output };  // Ошибка
	vector<double> previous_control_signal = {control_signal, control_signal};  // Предыдущие значения управляющего сигнала

	// Цикл, пока ошибка не станет меньше заданного порога
	while (abs(desired_output - output.back()) > 0.01)
	{
		error.push_back(desired_output - output.back());  // Обновление ошибки
		control_signal = previous_control_signal.back() + reg0 * error.back() + reg1 * error[error.size() - 2] + reg2 * error[error.size() - 3];
		// Рассчитываем новое значение выхода системы
		output.push_back(coeff_a * output.back() - coeff_b * output[output.size() - 2] + coeff_c * control_signal + coeff_d * sin(previous_control_signal.back()));
		previous_control_signal.push_back(control_signal);  // Сохраняем управляющий сигнал
	}

	// Вывод результатов
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < output.size(); i++)
		cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << previous_control_signal[i] << endl;
}

int main() {
	nonlinear_system();
}

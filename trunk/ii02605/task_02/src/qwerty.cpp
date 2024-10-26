#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double system_coeff_a = 0.5, system_coeff_b = 0.6, system_coeff_c = 0.6, system_coeff_d = 0.6;
// Параметры системы
double system_gain = 0.8, system_time_const_0 = 1.1, system_time_delay = 1.0, system_time_const = 1.1, target_output = 20;
// Параметры регулятора
double controller_gain_0 = system_gain * (1 + (system_time_delay / system_time_const_0)),
controller_gain_1 = -system_gain * (1 + 2 * (system_time_delay / system_time_const_0) - (system_time_const_0 / system_time_const)),
controller_gain_2 = system_gain * (system_time_delay / system_time_const_0);

void simulate_nonlinear_system() {
	// Начальные параметры
	const short int initial_system_output = 2;
	vector<double> system_output = { initial_system_output, initial_system_output };  // Выходные значения системы
	double control_signal = 1.0;  // Управляющий сигнал
	vector<double> error_signal = { target_output - initial_system_output, target_output - initial_system_output };  // Ошибка
	vector<double> previous_control_signals = { control_signal, control_signal };  // Предыдущие значения управляющего сигнала

	// Цикл, пока ошибка не станет меньше заданного порога
	while (abs(target_output - system_output.back()) > 0.01)
	{
		error_signal.push_back(target_output - system_output.back());  // Обновление ошибки
		control_signal = previous_control_signals.back() + controller_gain_0 * error_signal.back()
			+ controller_gain_1 * error_signal[error_signal.size() - 2]
			+ controller_gain_2 * error_signal[error_signal.size() - 3];
		// Рассчитываем новое значение выхода системы
		system_output.push_back(system_coeff_a * system_output.back()
			- system_coeff_b * system_output[system_output.size() - 2]
			+ system_coeff_c * control_signal
			+ system_coeff_d * sin(previous_control_signals.back()));
		previous_control_signals.push_back(control_signal);  // Сохраняем управляющий сигнал
	}

	// Вывод результатов
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < system_output.size(); i++)
		cout << i + 1 << ";" << system_output[i] << ";" << error_signal[i] << ";" << previous_control_signals[i] << endl;
}

int main() {
	simulate_nonlinear_system();
}

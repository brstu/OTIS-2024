#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double coeff_a, coeff_b, coeff_c, coeff_d;
// Параметры системы
double gain, time_const_0, time_delay, time_const, desired_output;
// Параметры регулятора
double reg_0, reg_1, reg_2;

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
		control_signal = previous_control_signal.back() + reg_0 * error.back() + reg_1 * error[error.size() - 2] + reg_2 * error[error.size() - 3];
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
	// Ввод параметров системы
	cout << "Введите коэффициенты системы:\n";
	cout << "coeff_a: "; cin >> coeff_a;
	cout << "coeff_b: "; cin >> coeff_b;
	cout << "coeff_c: "; cin >> coeff_c;
	cout << "coeff_d: "; cin >> coeff_d;

	// Ввод параметров системы
	cout << "Введите параметры системы:\n";
	cout << "gain: "; cin >> gain;
	cout << "time_const_0: "; cin >> time_const_0;
	cout << "time_delay: "; cin >> time_delay;
	cout << "time_const: "; cin >> time_const;
	cout << "desired_output (желаемое значение выхода): "; cin >> desired_output;

	// Расчет параметров регулятора
	reg_0 = gain * (1 + (time_delay / time_const_0));
	reg_1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
	reg_2 = gain * (time_delay / time_const_0);

	// Запуск моделирования
	nonlinear_system();

	return 0;
}

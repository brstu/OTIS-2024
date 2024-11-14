#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Коэффициенты системы
double koef_1, koef_2, koef_3, koef_4;
// Параметры системы
double gain, timekon_0, tm_del, tm_kon, des_out;
// Параметры регулятора
double rg_a, rg_b, rg_c;

void nonlinear_system() {
	// Начальные параметры
	const short int initial_output = 2;
	vector<double> output = { initial_output, initial_output };  // Выходные значения
	double control_signal = 1.0;  // Управляющий сигнал
	vector<double> error = { des_out - initial_output, des_out - initial_output };  // Ошибка
	vector<double> previous_control_signal = { control_signal, control_signal };  // Предыдущие значения управляющего сигнала

	// Цикл, пока ошибка не станет меньше заданного порога
	while (abs(des_out - output.back()) > 0.01)
	{
		error.push_back(des_out - output.back());  // Обновление ошибки
		control_signal = previous_control_signal.back() + rg_a * error.back() + rg_b * error[error.size() - 2] + rg_c * error[error.size() - 3];
		// Рассчитываем новое значение выхода системы
		output.push_back(koef_1 * output.back() - koef_2 * output[output.size() - 2] + koef_3 * control_signal + koef_4 * sin(previous_control_signal.back()));
		previous_control_signal.push_back(control_signal);  // Сохраняем управляющий сигнал
	}

	// Вывод результатов
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < output.size(); i++)
		cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << previous_control_signal[i] << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	// Ввод параметров системы
	cout << "Введите коэффициенты системы:\n";
	cout << "koef_1: "; cin >> koef_1;
	cout << "koef_2: "; cin >> koef_2;
	cout << "koef_3: "; cin >> koef_3;
	cout << "koef_4: "; cin >> koef_4;

	// Ввод параметров системы
	cout << "Введите параметры системы:\n";
	cout << "gain: "; cin >> gain;
	cout << "timekon_0: "; cin >> timekon_0;
	cout << "tm_del: "; cin >> tm_del;
	cout << "tm_kon: "; cin >> tm_kon;
	cout << "des_out (желаемое значение выхода): "; cin >> des_out;

	// Расчет параметров регулятора
	rg_a = gain * (1 + (tm_del / timekon_0));
	rg_b = -gain * (1 + 2 * (tm_del / timekon_0) - (timekon_0 / tm_kon));
	rg_c = gain * (tm_del / timekon_0);

	// Запуск моделирования
	nonlinear_system();

	return 0;
}
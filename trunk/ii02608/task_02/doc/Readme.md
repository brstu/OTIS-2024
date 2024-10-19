<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Кушнеревич Е.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Код программы: #
```C++
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
```     
Вывод программы: 
```
Введите коэффициенты системы:
coeff_a: 0.8
coeff_b: 0.4
coeff_c: 0.4
coeff_d: 0.7
Введите параметры системы:
gain: 0.9
time_const_0: 1
time_delay: 1.2
time_const: 1
desired_output (желаемое значение выхода): 20
Step    Output  Error   Control Signal
1;2;18;1
2;2;18;1
3;8.26903;18;17.2
4;13.5123;11.731;20.9873
5;19.2663;6.48768;27.934
6;21.4589;0.73367;28.0428
7;21.8517;-1.45888;30.5761
8;20.718;-1.85169;30.8533
9;20.2027;-0.717983;31.8558
10;20.5752;-0.202669;31.0055
11;19.9114;-0.575224;29.5289
12;19.3249;0.0885996;30.728
13;19.5517;0.675083;31.252
14;20.108;0.448305;30.7772
15;19.978;-0.108018;30.324
16;19.752;0.0219984;31.0851
17;20.1478;0.248028;31.412
18;20.4576;-0.147781;30.6074
19;19.9161;-0.457645;30.2883
20;19.6308;0.0839447;31.2835
21;20.1813;0.369192;31.3389
22;20.3481;-0.181328;30.2731
23;19.7188;-0.348092;30.3742
24;19.6263;0.28124;31.4871
25;20.3608;0.373654;31.2436
26;20.3284;-0.3608;30.0258
27;19.6532;-0.328365;30.5585
28;19.6878;0.346821;31.5648
29;20.4245;0.312167;31.0792
30;20.2087;-0.424513;29.9389
31;19.6121;-0.208737;30.7797
32;19.8063;0.387859;31.5401
33;20.431;0.193672;30.8603
34;20.056;-0.431004;30.0075
35;19.5963;-0.0560459;31.0367
36;19.9921;0.403699;31.4915
![График](unliner.png)


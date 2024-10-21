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
<p align="right">Рудь В.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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
```
Вывод:
```
1;2;18;1
2;2;18;1
3;9.54488;18;15.4
4;14.7205;10.4551;18.2769
5;15.8424;5.27954;24.2237
6;16.9143;4.15761;30.4979
7;18.2768;3.08572;33.0028
8;20.0918;1.72325;34.1701
9;19.567;-0.0917899;33.7675
10;19.644;0.432959;35.8156
11;18.9085;0.35601;35.6628
12;19.4078;1.09146;37.1268
13;20.0554;0.592205;36.7026
14;19.8095;-0.055358;36.5504
15;19.7358;0.190501;37.3526
16;20.2417;0.264249;37.4388
17;20.2193;-0.241687;36.8239
18;19.7236;-0.219299;37.0327
19;19.9181;0.276374;37.598
20;20.3612;0.0818919;37.1616
21;19.9376;-0.361241;36.6917
22;19.668;0.0624235;37.3721
23;20.1941;0.331975;37.5256
24;20.2676;-0.194062;36.7917
25;19.6886;-0.267637;36.9067
26;19.8347;0.311366;37.6304
27;20.4041;0.165296;37.2353
28;19.9953;-0.404112;36.6041
```
![График](unliner.png)

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
<p align="right">Хомиченко И.А.</p>
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
```     
Вывод программы: 
```
Введите коэффициенты системы:
c_a: 0.5
c_b: 0.2
c_c: 0.6
c_d: 0.4
Введите параметры системы:
k: 1
t_const_0: 1
t_delay: 2
t_const: 2
des_output (желаемое значение выхода): 4
Step    Output  Error   Control Signal
1;2;2;1
2;2;2;1
3;2.13659;2;2
4;2.58615;1.86341;2.59023
5;2.54315;1.41385;2.44642
6;3.51944;1.45685;4.18149
7;2.04316;0.480556;1.89502
8;5.80689;1.95684;8.51673
9;-0.0390218;-1.80689;-4.74859
10;10.8667;4.03902;19.4132
11;-8.131;-6.86674;-22.9764
12;25.5315;12.131;52.3949
13;-33.5824;-21.5315;-80.5225
14;70.496;37.5824;153.378
15;-112.799;-66.496;-258.293
16;209.149;116.799;466.501
17;-356.987;-205.149;-807.536
18;639.053;360.987;1432.2
19;-1113.84;-635.053;-2507.7
20;1970.33;1117.84;4425.54
21;-3456.04;-1966.33;-7773.85
22;6091.78;3460.04;13690.5
23;-10708.6;-6087.78;-24075.8
24;18854;10712.6;42377.1
25;-33164.4;-18850;-74555.1
26;58367.6;33168.4;131200
27;-102692;-58363.6;-230848
28;180708;102696;406212
29;-317963;-180704;-714759
30;559499;317967;1.2577e+06
31;-984483;-559495;-2.21304e+06
32;1.73231e+06;984487;3.89408e+06
33;-3.04816e+06;-1.7323e+06;-6.85201e+06
34;5.36355e+06;3.04816e+06;1.20568e+07
35;-9.43768e+06;-5.36354e+06;-2.12151e+07
36;1.66066e+07;9.43769e+06;3.73302e+07
37;-2.92209e+07;-1.66066e+07;-6.56862e+07
38;5.14171e+07;2.92209e+07;1.15581e+08

![График](unliner.png)
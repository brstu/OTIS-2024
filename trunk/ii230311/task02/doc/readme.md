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
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Пасевич К. Ю.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


<hr>

# Выполнение задания #

Код программы:
```C++
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
'''
Вывод:
'''
Ваше стартовое значение:5
0
0
0
4.86256
6.087
5.37458
4.20085
4.49149
5.367
5.42736
4.83152
4.62285
5.00913
5.25095
5.05321
4.82133
4.9064
5.09265
5.08388
4.94846
4.9186
5.00806
5.0531
5.00188
4.95573
4.98036
5.0199
5.0131
4.98307
4.97998
5.00072
5.00856
4.99594
4.98702
4.99375
5.00201
4.9995
4.993
4.99314
4.9979
4.99917
4.99618
4.99456
4.99634
4.99806
4.99733
4.99599
4.99623
4.99734
4.99755
4.99689
4.99665
4.99714
4.99752
4.99736
4.99712
4.99726
4.99755
4.99761
4.9975
4.99751
4.99767
4.99779
4.99779
4.99779
4.99787
4.99798
4.99803
4.99805
4.9981
4.99818
4.99825
4.99829
4.99834
4.9984
4.99847
4.99852
4.99857
4.99863
4.99869
4.99875
4.9988
4.99886
4.99892
4.99898
4.99903
4.99909
4.99915
4.9992
4.99926
4.99932
4.99937
4.99943
4.99949
4.99954
4.9996
4.99966
4.99972
4.99977
4.99983
4.99989
4.99994
5
'''

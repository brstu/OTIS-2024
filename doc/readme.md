<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Ковальчук А. И.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**Julia**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```#include <iostream>
#include <cmath>
using namespace std;

const double a = 0.95, b = 0.2, c = 1.0, d = 1.5;

double linear_model(double& y, double& u)
{
	y = a * y + b * u;
	return y;
}

double unlinear_model(double& y, double& y_pred, double& y_penultimate, double& u, bool& firstIter)
{
	if (firstIter)
	{
		y_penultimate = y;
		y_pred = a * y + c * u + d*sin(u);
		y = y_pred;
		firstIter = false;
		return y_pred;
	}
	else
	{
		y_pred = a * y - b * pow(y_penultimate, 2) + c * u + d * sin(u);
		y_penultimate = y;
		y = y_pred;
		return y_pred;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double u, y_linear, y_unlinear, y_pred, y_penultimate;
	int N;
	bool firstIter = true;

	cout << "Введите начальное значение температуры: ";
	cin >> y_linear;
	y_unlinear = y_linear;

	cout << "\nВведите значение тепла: "; 
	cin >> u;

	cout << "\nВведите количество итераций: ";
	cin >> N;

	cout << "\nРезультаты вычислений линейной модели: " << endl;
	for (size_t i = 0; i < N; i++)
		cout << i << ") " << linear_model(y_linear, u) << endl;

	cout << "\nРезультаты вычислений нелинейной модели: " << endl;
	for(size_t i=0; i<N; i++)
		cout << i << ") " << unlinear_model(y_unlinear, y_pred, y_penultimate, u, firstIter) << endl;

	return 0;
}
```     
```
Введите количество итераций: 10

Результаты вычислений линейной модели:
0) 2.255
1) 2.40225
2) 2.54214
3) 2.67503
4) 2.80128
5) 2.92122
6) 3.03515
7) 3.1434
8) 3.24623
9) 3.34392

Результаты вычислений нелинейной модели:
0) 4.74034
1) 6.36666
2) 4.2995
3) -1.277
4) -2.16496
5) 0.36248
6) 2.15228
7) 4.76373
8) 6.34441
9) 4.23391
```
![График](./graphics.png)

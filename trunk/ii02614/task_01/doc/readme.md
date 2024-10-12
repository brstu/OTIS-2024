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
<p align="right">Рудь В. В.</p>
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
```C++
#include<iostream>
#include<cmath>

using namespace std;

double coeff_a = 1.0, 
coeff_b = 0.5, 
coeff_c = 0.1, 
coeff_d = 0.9, 
input_u = 1.5;

void linear_model(double& temp_linear)
{
	temp_linear = coeff_a * temp_linear + coeff_b * input_u;
	cout << "|" << temp_linear  << endl;
}

void nonlinear_model(double& temp_nonlinear, double& prev_temp_nonlinear, bool& is_first_iteration)
{
	if (is_first_iteration) {
		prev_temp_nonlinear = temp_nonlinear;
		temp_nonlinear = coeff_a * temp_nonlinear + coeff_c * input_u + coeff_d * sin(input_u);
		is_first_iteration = false; // первая итерация закончена
		cout << "|" << temp_nonlinear << endl;
	}
	else {
		double temp_new = 0; // переменная для хранения значения новой температуры 
		temp_new = coeff_a * temp_nonlinear - coeff_b * pow(prev_temp_nonlinear, 2) + coeff_c * input_u + coeff_d * sin(input_u);
		prev_temp_nonlinear = temp_nonlinear; // устанавливаем новое значение для предыдущего значения
		temp_nonlinear = temp_new; // устанавливаем новое значение для текущего значения
		cout << "|" << temp_nonlinear << endl;
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	double temp_linear = 0, temp_nonlinear = 0, prev_temp_nonlinear = 0; 
	bool is_first_iteration = true; // используется для определения первой итерации в функции нелинейной модели 
	cout << "Введите начальную температуру:";
	cin >> temp_linear;
	temp_nonlinear = temp_linear;
	int iterations = 10;
	cout << "Линейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		linear_model(temp_linear);
	}
	cout << "Нелинейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		nonlinear_model(temp_nonlinear, prev_temp_nonlinear, is_first_iteration);
	}
	return 0;
}
```     
```
Вывод программы:
линейная модель:
|0.85
|1.6
|2.35
|3.1
|3.85
|4.6
|5.35
|6.1
|6.85
|7.6
нелинейная модель:
|1.14775
|2.19049
|2.57958
|1.2282
|-1.05117
|-0.757654
|-0.262383
|0.498343
|1.51167
|2.43524```
![График](./graphics.png)

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
<p align="right">Шарубнёв Д. С.</p>
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

double a = 1.0,
b = 0.5,
c = 0.1,
d = 0.9,
u = 1.5;

void liner_model(double& y_liner)
{
	y_liner = a * y_liner + b * u;
	cout << "|" << y_liner << endl;
}

void unliner_model(double& y_unliner, double& pre_y_unliner, bool& first)
{
	if (first) {
		pre_y_unliner = y_unliner;
		y_unliner = a * y_unliner + c * u + d * sin(u);
		first = false; // первая итерция закончена
		cout << "|" << y_unliner << endl;
	}
	else {
		double vr = 0; // переменная для хранения значения новой температуры 
		vr = a * y_unliner - b * pow(pre_y_unliner, 2) + c * u + d * sin(u);
		pre_y_unliner = y_unliner; //устанавливаем новое значение для преведущего значения у
		y_unliner = vr;//устанавливаем новое значение для текущего значения у
		cout << "|" << y_unliner << endl;
	}
}


int main() {
	setlocale(LC_ALL, "rus");
	double y_liner = 0, y_unliner = 0, pre_y_unliner = 0;
	bool first = true; //используется для определения первой итерации в функции нелинейной модели 
	cout << "Введите начальную температуру:";
	cin >> y_liner;
	y_unliner = y_liner;
	int N = 10;
	cout << "линейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		liner_model(y_liner);
	}
	cout << "нелинейная модель:" << endl;
	for (int i = 0; i < N; i++) {
		unliner_model(y_unliner, pre_y_unliner, first);
	}
	return 0;
}
```     
```
Введите начальную температуру:1
линейная модель:
|1.75
|2.5
|3.25
|4
|4.75
|5.5
|6.25
|7
|7.75
|8.5
нелинейная модель:
|2.04775
|2.59549
|1.54661
|-0.773936
|-0.922185
|-0.173927
|0.448606
|1.48123
|2.42835
|2.37908
```
![График](./graphics.png)

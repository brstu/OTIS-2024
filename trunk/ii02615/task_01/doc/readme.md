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
<p align="right">Рулько М. А.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец А. А.</p>
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



double coeff_a = 1.0,
b = 0.5,
c = 0.1,
d = 0.9,
U = 1.5;

using namespace std;

void LINEYKA(double& TLEN);
void nonLINEYKA(double& temp_nonlinear, double& prev_temp_nonlinear, bool& is_first_iteration);


int main() {
	setlocale(LC_ALL, "rus");
	double TLEN = 0, temp_nonlinear = 0, prev_temp_nonlinear = 0;
	bool is_first_iteration = true; // используется для определения первой итерации в функции нелинейной модели 
	cout << "какая начальная температура?";
	cin >> TLEN;
	temp_nonlinear = TLEN;


	int iterations = 10;
	cout << "линейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		LINEYKA(TLEN);
	}

	cout << "нелинейная модель:" << endl;
	for (int i = 0; i < iterations; i++) {
		nonLINEYKA(temp_nonlinear, prev_temp_nonlinear, is_first_iteration);
	}

	return 0;
}
void LINEYKA(double& TLEN)
{
	TLEN = coeff_a * TLEN + b * U;
	cout << "////" << TLEN <<  "////" << endl;
}
void nonLINEYKA(double& temp_nonlinear, double& prev_temp_nonlinear, bool& is_first_iteration)
{
	if (is_first_iteration) {
		prev_temp_nonlinear = temp_nonlinear;
		temp_nonlinear = coeff_a * temp_nonlinear + c * U + d * sin(U);
		is_first_iteration = false; // первая итерация закончена
		cout << "////"   << temp_nonlinear << "////" << endl;
	}
	else {
		double temp_new = 0; // переменная для хранения значения новой температуры 
		temp_new = coeff_a * temp_nonlinear - b * pow(prev_temp_nonlinear, 2) + c * U + d * sin(U);
		prev_temp_nonlinear = temp_nonlinear; // устанавливаем новое значение для предыдущего значения
		temp_nonlinear = temp_new; // устанавливаем новое значение для текущего значения
		cout << "////"  << temp_nonlinear << "////" << endl;
	}
}
```     
```
Вывод программы:
какая начальная температура?10
линейная модель:
////10.75////
////11.5////
////12.25////
////13////
////13.75////
////14.5////
////15.25////
////16////
////16.75////
////17.5////
нелинейная модель:
////11.0477////
////-37.9045////
////-97.8831////
////-815.211////
////-5604.71////
////-337888////
////-1.60443e+07////
////-5.71003e+10////
////-1.28767e+14////
////-1.63022e+21////

![График](./graphics.png)

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
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Пасевич К. Ю.</p>
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
#include <iostream>
#include <cmath>
using namespace std;
 // Неизменные
const double  A = 0.6;
const double B = 0.002;
const double C = 0.4;
const double D = 0.6;
// Функция для линейной модели
void linearMod(double U, int totalSteps, double Y) {
	for (int i = 1; i <= totalSteps; ++i) {
		cout << "Time:" << i << ", LinearOut : " << Y << endl;
		Y = A * Y + B * U; // Обновление значения
	}
	cout << "---------------------\"n";
}
			// Функция для нелинейной модели
			 void nonlinearMod(double U, int totalSteps, double Y, double Y1) {
			for (int i = 1; i <= totalSteps; ++i) {
				cout << "Time: " << i << ", NonlinearOut: " << Y << endl;
				double newY = A * Y - B * Y1 * Y1 + C * U + D * sin(U); // Обновление значения; // Сохранение предыдущего значения; // Обновление текущего значения
			}
		}
		int main() {
			setlocale(LC_ALL, "rus");
			double U; // Начальное тепло
			int totalSteps = 45; // Количество итераций
			double Y; // Нулевое значение для линейной модели 
			double Y1;  // Нулевое значение для нелинейной модели
		
				
				// Ввод данных вручную
			cout << "Введите входное тепло: ";
				cin >> U;
			cout <<"Введите начальное значение для линейной модели: ";
			cin >> Y;
			cout << "Введите начальное значение для нелинейной модели: ";
			cin >> Y1;
			cout << "linear model: \n";
				linearMod(U, totalSteps, Y);
			cout << "Nonlinear model: \n";
			nonlinearMod(U, totalSteps, Y, Y1);
			return 0;
		}
```     
```
Введите входное тепло: 1
Введите начальное значение для линейной модели: 3
Введите начальное значение для нелинейной модели: 4
linear model:
Time:1, LinearOut : 3
Time:2, LinearOut : 1.802
Time:3, LinearOut : 1.0832
Time:4, LinearOut : 0.65192
Time:5, LinearOut : 0.393152
Time:6, LinearOut : 0.237891
Time:7, LinearOut : 0.144735
Time:8, LinearOut : 0.0888408
Time:9, LinearOut : 0.0553045
Time:10, LinearOut : 0.0351827
Time:11, LinearOut : 0.0231096
Time:12, LinearOut : 0.0158658
Time:13, LinearOut : 0.0115195
Time:14, LinearOut : 0.00891168
Time:15, LinearOut : 0.00734701
Time:16, LinearOut : 0.0064082
Time:17, LinearOut : 0.00584492
Time:18, LinearOut : 0.00550695
Time:19, LinearOut : 0.00530417
Time:20, LinearOut : 0.0051825
Time:21, LinearOut : 0.0051095
Time:22, LinearOut : 0.0050657
Time:23, LinearOut : 0.00503942
Time:24, LinearOut : 0.00502365
Time:25, LinearOut : 0.00501419
Time:26, LinearOut : 0.00500851
Time:27, LinearOut : 0.00500511
Time:28, LinearOut : 0.00500307
Time:29, LinearOut : 0.00500184
Time:30, LinearOut : 0.0050011
Time:31, LinearOut : 0.00500066
Time:32, LinearOut : 0.0050004
Time:33, LinearOut : 0.00500024
Time:34, LinearOut : 0.00500014
Time:35, LinearOut : 0.00500009
Time:36, LinearOut : 0.00500005
Time:37, LinearOut : 0.00500003
Time:38, LinearOut : 0.00500002
Time:39, LinearOut : 0.00500001
Time:40, LinearOut : 0.00500001
Time:41, LinearOut : 0.005
Time:42, LinearOut : 0.005
Time:43, LinearOut : 0.005
Time:44, LinearOut : 0.005
Time:45, LinearOut : 0.005
---------------------"nNonlinear model:
Time: 1, NonlinearOut: 3
Time: 2, NonlinearOut: 3
Time: 3, NonlinearOut: 3
Time: 4, NonlinearOut: 3
Time: 5, NonlinearOut: 3
Time: 6, NonlinearOut: 3
Time: 7, NonlinearOut: 3
Time: 8, NonlinearOut: 3
Time: 9, NonlinearOut: 3
Time: 10, NonlinearOut: 3
Time: 11, NonlinearOut: 3
Time: 12, NonlinearOut: 3
Time: 13, NonlinearOut: 3
Time: 14, NonlinearOut: 3
Time: 15, NonlinearOut: 3
Time: 16, NonlinearOut: 3
Time: 17, NonlinearOut: 3
Time: 18, NonlinearOut: 3
Time: 19, NonlinearOut: 3
Time: 20, NonlinearOut: 3
Time: 21, NonlinearOut: 3
Time: 22, NonlinearOut: 3
Time: 23, NonlinearOut: 3
Time: 24, NonlinearOut: 3
Time: 25, NonlinearOut: 3
Time: 26, NonlinearOut: 3
Time: 27, NonlinearOut: 3
Time: 28, NonlinearOut: 3
Time: 29, NonlinearOut: 3
Time: 30, NonlinearOut: 3
Time: 31, NonlinearOut: 3
Time: 32, NonlinearOut: 3
Time: 33, NonlinearOut: 3
Time: 34, NonlinearOut: 3
Time: 35, NonlinearOut: 3
Time: 36, NonlinearOut: 3
Time: 37, NonlinearOut: 3
Time: 38, NonlinearOut: 3
Time: 39, NonlinearOut: 3
Time: 40, NonlinearOut: 3
Time: 41, NonlinearOut: 3
Time: 42, NonlinearOut: 3
Time: 43, NonlinearOut: 3
Time: 44, NonlinearOut: 3
Time: 45, NonlinearOut: 3```

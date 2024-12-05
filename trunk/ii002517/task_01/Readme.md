@@ -0,0 +1,120 @@
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
<p align="right">Группы ИИ-25</p>
<p align="right">Нешумаев А.К.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
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
Task is to write program (**C++**), which simulates this object temperature.
<hr>
# Выполнение задания #
Код программы:
```C++
#include <iostream>
#include <vector>
#include <cmath>
class TempratureControle {
public:
	double a;
	double b;
	double c;
	double d;
	double u;
	int t;
	std::vector<double>y{ 1.1, };
	std::vector<double>yy{ 1.1, };
	void linear_f() {
		double y_1 = a * y.back() + b * u;
		y.push_back(y_1);
	}
	void non_linear_f() {
		double y_1 = a * yy.back() - b * pow(yy.back(), 2) + c * u + d * sin(u);
		yy.push_back(y_1);
	}

	TempratureControle(double a, double b, double c, double d, double u, int t) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->u = u;
		this->t = t;
	}
};
int main() {
	TempratureControle obj(0.6, 0.8, 0.2, 1.0, 0.2, 15);
	for (int i = 0; i < obj.t; i++) {
		obj.linear_f();
	}
	for (int i = 0; i < obj.t; i++) {
		obj.non_linear_f();
	}
	for (int i = 0; i < obj.y.size(); i++) {
		std::cout << obj.y[i] << " ";
		std::cout << obj.yy[i] << std::endl;
	}
	return 0;
}


```     
```
Введите начальное T: 1
Введите шаг: 10
       It:    Linear    No-Linear
         0         1            1
         1      0.76     0.838669
         2     0.616    -0.058129
         3    0.5296    -0.358901
         4   0.47776    0.0206255
         5  0.446656     0.147997
         6  0.427994     0.327127
         7  0.416796     0.417423
         8  0.410078     0.403514
         9  0.406047     0.341384
        10  0.403628     0.313241
```
![График](./graphic.png)
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
<p align="right">Петручик Д. А.</p>
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

Task is to write program (**С++**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <vector>
#include <cmath>  

using namespace std;

double linearModel(double alfa, double beta, double y_tau, double u_tau) {
    return alfa * y_tau + beta * u_tau;
}

double nonlinearModel(double alfa, double beta, double gama, double delta, double y_tau, double y_tau_1, double u_tau, double u_tau_1) {
    return alfa * y_tau - beta * pow(y_tau_1, 2) + gama * u_tau + delta * sin(u_tau_1);
}

int main() {

    setlocale(LC_ALL, "RU");

    double alfa = 0.5, beta = 0.2, gama = 0.2, delta = 0.8;
    double y_0 = 1;
    double u_0 = 1;
    int n = 10;

    vector<double> y(n + 1);
    vector<double> u(n + 1);

    y[0] = y_0;
    u[0] = u_0;

    cout << "Линейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        y[tau] = linearModel(alfa, beta, y[tau - 1], u[0]);
        cout << y[tau] << endl;
    }

    y[0] = y_0;

    cout << "Нелинейная модель:\n";
    for (int tau = 1; tau <= n; ++tau) {
        if (tau == 1) {
            y[tau] = linearModel(alfa, beta, y[tau - 1], u[0]);
        }
        else {
            y[tau] = nonlinearModel(alfa, beta, gama, delta, y[tau - 1], y[tau - 2], u[0], u[0]);
        }
        cout << y[tau] << endl;
    }
    return 0;
}

Линейная модель:
0.7
0.55
0.475
0.4375
0.41875
0.409375
0.404688
0.402344
0.401172
0.400586
Нелинейная модель:
0.7
1.02318
1.28677
1.30718
1.19561
1.12924
1.1519
1.19409
1.20485
1.19043
![График](image.png)
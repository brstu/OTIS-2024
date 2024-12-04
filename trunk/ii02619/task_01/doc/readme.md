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
<p align="right">Турич Д. А.</p>
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

const double alfa = 0.6; 
const double beta = 0.2; 
const double gamma = 0.01;
const double delta = 0.4; 


double rpex(double u_prev) {
    return exp(-u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 9; 
    double y_0 = 10; 
    double u_0 = 10; 
    vector<double> y_linear(n + 1, y_0);
    vector<double> y_nonlinear(n + 1, y_0);

    
    for (int t = 0; t < n; ++t) {
        // Линейная модель
        y_linear[t + 1] = alfa * y_linear[t] + beta * u_0;

        // Нелинейная модель
        double u_prev = (t > 0) ? u_0 : 0.0; 
        y_nonlinear[t + 1] = alfa * y_nonlinear[t] - beta * pow(y_nonlinear[t], 2) + gamma * u_0 + delta * rpex(u_prev);
    }

    
    cout << "Временной шаг\tЛинейная модель\tНелинейная модель\n";
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t\t" << y_linear[t] << "\t\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
```     
```
Временной шаг   Линейная модель Нелинейная модель
0               10              10
1               8               -13.5
2               6.8             -44.45
3               6.08            -421.73
4               5.648           -35824.2
5               5.3888          -2.56696e+08
6               5.23328         -1.31786e+16
7               5.13997         -3.4735e+31
8               5.08398         -2.41304e+62
9               5.05039         -1.16456e+124

![График](image.png)
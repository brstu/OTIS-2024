<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Мохорева Т. Д.</p>
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
#include <cmath>
using namespace std;

double calculateNextLinearValue(double a, double b, double u, const double& y) {
    return a * y + b * u;
}

void setLinearOutput(double& y, double newY) {
    y = newY;
}

void displayLinearModel(const double& y, double a, double b, double u, int iterations) {
    cout << "Linear model" << endl;
    double currentY = y;
    for (int i = 0; i < iterations; ++i) {
        cout << currentY << endl;
        double newY = calculateNextLinearValue(a, b, u, currentY);
        setLinearOutput(currentY, newY);
    }
}

double calculateNextNonlinearValue(double a, double b, double c, double d, double u, const double& y, const double& prevY) {
    if (prevY == 0) {
        return a * y - b * pow(prevY, 2) + c * 1 + d * sin(1);
    }
    else {
        return a * y - b * pow(prevY, 2) + c * u + d * sin(u);
    }
}

void setNonlinearOutput(double& y, double& prevY, double newY) {
    prevY = y;
    y = newY;
}

void displayNonlinearModel(const double& y, double a, double b, double c, double d, double u, int iterations) {
    cout << "Nonlinear model" << endl;
    double currentY = y;
    double previousY = 0.0;
    for (int i = 0; i < iterations; ++i) {
        cout << currentY << endl;
        double newY = calculateNextNonlinearValue(a, b, c, d, u, currentY, previousY);
        setNonlinearOutput(currentY, previousY, newY);
    }
}

int main() {
    // Параметры для линейной модели
    const double linearA = 0.3;
    const double linearB = 0.3;
    const double linearU = 0.9;
    double linearY = 0.0;
    const int linearIterations = 10;

    displayLinearModel(linearY, linearA, linearB, linearU, linearIterations);

    // Параметры для нелинейной модели
    const double nonlinearA = 0.1;
    const double nonlinearB = 0.2;
    const double nonlinearC = 0.4;
    const double nonlinearD = 0.2;
    const double nonlinearU = 0.8;
    double nonlinearY = 0.0;
    const int nonlinearIterations = 10;

    displayNonlinearModel(nonlinearY, nonlinearA, nonlinearB, nonlinearC, nonlinearD, nonlinearU, nonlinearIterations);

    return 0;
}
```     
```
Linear model
0
0.27
0.351
0.3753
0.38259
0.384777
0.385433
0.38563
0.385689
0.385707
Nonlinear model
0
0.568294
0.625124
0.461392
0.431455
0.46404
0.472645
0.467669
0.46556
0.466284
```
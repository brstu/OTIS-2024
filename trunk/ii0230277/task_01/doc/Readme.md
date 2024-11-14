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
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Бекназаровой А. С.</p>
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
#include <cmath>

// Константы
const double a = 0.5;  // Пример значения
const double b = 0.1;  // Пример значения
const double c = 0.05; // Пример значения
const double d = 0.01; // Пример значения

const int time_steps = 100; // Количество шагов по времени

void simulate_linear_model(double y[], double u[]) {
    for (int t = 0; t < time_steps; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
        std::cout << "Linear Model at time " << t << ": " << y[t + 1] << std::endl;
    }
}

void simulate_nonlinear_model(double y[], double u[]) {
    for (int t = 1; t < time_steps; ++t) {
        y[t + 1] = a * y[t] - b * y[t - 1] * y[t - 1] + c * y[t] + d * std::sin(u[t - 1]);
        std::cout << "Nonlinear Model at time " << t << ": " << y[t + 1] << std::endl;
    }
}

int main() {
    double y[time_steps + 1] = { 0 }; // Инициализация массива температур
    double u[time_steps] = { 0 };   // Инициализация массива теплового воздействия

    // Пример заполнения массива u значениями теплового воздействия
    for (int t = 0; t < time_steps; ++t) {
        u[t] = 1.0; // Например, постоянное воздействие
    }

    // Симуляция линейной модели
    simulate_linear_model(y, u);

    // Симуляция нелинейной модели
    simulate_nonlinear_model(y, u);

    return 0;
}

```     
```
Временной шаг   Линейная модель Нелинейная модель
0               0.15             0.0634147
1               0.175            0.0422928
2               0.1875           0.0312736
3               0.19375          0.0254363
4               0.196875         0.0223069
5               0.198438         0.0206188
6               0.199219         0.0197053
7               0.199609         0.0192101
8               0.199805         0.0189414
9               0.199902         0.0187956
10              0.199952         0.0187164
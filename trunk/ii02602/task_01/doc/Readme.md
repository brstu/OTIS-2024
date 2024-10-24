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
<p align="right">Данилюк Т. В.</p>
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
using namespace std;

double linearModelStep(double a, double b, double y, double u) {
    return a * y + b * u;
}

double nonlinearModelStep(double a, double b, double c, double d, double y, double y_prev, double u) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u);
}

void runSimulation(double a, double b, double c, double d, double y0, double u0, int num_steps) {
    double y_linear = y0;
    double u = u0;

    cout << "Результаты для линейной модели:\n";
    for (int t = 0; t < num_steps; ++t) {
        double y_next = linearModelStep(a, b, y_linear, u);
        cout << "Шаг " << t << ": Температура = " << y_next << endl;
        y_linear = y_next;
    }

    double y_prev = y0;
    double y_nonlinear = y0;

    cout << "\nРезультаты для нелинейной модели:\n";
    for (int t = 0; t < num_steps; ++t) {
        double y_next = nonlinearModelStep(a, b, c, d, y_nonlinear, y_prev, u);
        cout << "Шаг " << t << ": Температура = " << y_next << endl;
        y_prev = y_nonlinear;
        y_nonlinear = y_next;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a, b, c, d;
    double initial_temperature, initial_input;
    int num_steps;

    cout << "Введите значение параметра a: ";
    cin >> a;
    cout << "Введите значение параметра b: ";
    cin >> b;
    cout << "Введите значение параметра c (для нелинейной модели): ";
    cin >> c;
    cout << "Введите значение параметра d (для нелинейной модели): ";
    cin >> d;
    cout << "Введите начальное значение температуры y0: ";
    cin >> initial_temperature;
    cout << "Введите начальное значение управляющего сигнала u0: ";
    cin >> initial_input;
    cout << "Введите количество шагов моделирования: ";
    cin >> num_steps;

    runSimulation(a, b, c, d, initial_temperature, initial_input, num_steps);

    return 0;
}
```     
```
Введите значение параметра d (для нелинейной модели): 0.8
Введите начальное значение температуры y0: 40
Введите начальное значение управляющего сигнала u0: 15
Введите количество шагов моделирования: 10
Результаты для линейной модели:
Шаг 0: Температура = 41.35
Шаг 1: Температура = 42.7
Шаг 2: Температура = 44.05
Шаг 3: Температура = 45.4
Шаг 4: Температура = 46.75
Шаг 5: Температура = 48.1
Шаг 6: Температура = 49.45
Шаг 7: Температура = 50.8
Шаг 8: Температура = 52.15
Шаг 9: Температура = 53.5

Результаты для нелинейной модели:
Шаг 0: Температура = -95.9798
Шаг 1: Температура = -231.96
Шаг 2: Температура = -1053.03
Шаг 3: Температура = -5887.48
Шаг 4: Температура = -105678
Шаг 5: Температура = -3.22529e+06
Шаг 6: Температура = -1.00833e+09
Шаг 7: Температура = -9.37232e+11
Шаг 8: Температура = -9.15064e+16
Шаг 9: Температура = -7.90564e+22

![График](graphics.png)
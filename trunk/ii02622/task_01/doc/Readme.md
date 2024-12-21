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
<p align="right">Цурукова В. А.</p>
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

double computeLinearStep(double alpha, double beta, double temp, double control) {
    return alpha * temp + beta * control;
}

double computeNonlinearStep(double alpha, double beta, double gamma, double delta, double temp, double prev_temp, double control) {
    return alpha * temp - beta * prev_temp * prev_temp + gamma * control + delta * sin(control);
}

void performSimulation(double alpha, double beta, double gamma, double delta, double initial_temp, double initial_control, int steps) {
    double linear_temp = initial_temp;
    double control_signal = initial_control;

    cout << "Результаты линейной модели:\n";
    for (int step = 0; step < steps; ++step) {
        double next_temp = computeLinearStep(alpha, beta, linear_temp, control_signal);
        cout << "Шаг " << step << ": Температура = " << next_temp << endl;
        linear_temp = next_temp;
    }

    double prev_temp = initial_temp;
    double nonlinear_temp = initial_temp;

    cout << "\nРезультаты нелинейной модели:\n";
    for (int step = 0; step < steps; ++step) {
        double next_temp = computeNonlinearStep(alpha, beta, gamma, delta, nonlinear_temp, prev_temp, control_signal);
        cout << "Шаг " << step << ": Температура = " << next_temp << endl;
        prev_temp = nonlinear_temp;
        nonlinear_temp = next_temp;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double alpha, beta, gamma, delta;
    double init_temp, init_control;
    int steps;

    cout << "Введите значение параметра alpha: ";
    cin >> alpha;
    cout << "Введите значение параметра beta: ";
    cin >> beta;
    cout << "Введите значение параметра gamma (для нелинейной модели): ";
    cin >> gamma;
    cout << "Введите значение параметра delta (для нелинейной модели): ";
    cin >> delta;
    cout << "Введите начальное значение температуры: ";
    cin >> init_temp;
    cout << "Введите начальное значение управляющего сигнала: ";
    cin >> init_control;
    cout << "Введите количество шагов моделирования: ";
    cin >> steps;

    performSimulation(alpha, beta, gamma, delta, init_temp, init_control, steps);

    return 0;
}
```     
```
Введите значение параметра alpha: 0.9
Введите значение параметра beta: 0.3
Введите значение параметра gamma (для нелинейной модели): 0.4
Введите значение параметра delta (для нелинейной модели): 0.1
Введите начальное значение температуры: 2.0
Введите начальное значение управляющего сигнала: 1.0
Введите количество шагов моделирования: 10
Результаты линейной модели:
Шаг 0: Температура = 2.1
Шаг 1: Температура = 2.19
Шаг 2: Температура = 2.271
Шаг 3: Температура = 2.3439
Шаг 4: Температура = 2.40951
Шаг 5: Температура = 2.46856
Шаг 6: Температура = 2.5217
Шаг 7: Температура = 2.56953
Шаг 8: Температура = 2.61258
Шаг 9: Температура = 2.65132

Результаты нелинейной модели:
Шаг 0: Температура = 1.08415
Шаг 1: Температура = 0.259879
Шаг 2: Температура = 0.365426
Шаг 3: Температура = 0.792769
Шаг 4: Температура = 1.15758
Шаг 5: Температура = 1.33742
Шаг 6: Температура = 1.28583
Шаг 7: Температура = 1.10479
Шаг 8: Температура = 0.982445
Шаг 9: Температура = 1.00218

![График](graphics.png)
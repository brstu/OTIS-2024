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
<p align="right">Заседатель Н.С.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я.С.</p>
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

void runLinearSimulation(double alpha, double beta, double temp0, double control0, int steps_count) {
    double current_temp = temp0; 
    double control_signal = control0; 

    cout << "Линейная модель:\n";
    for (int step = 0; step < steps_count; ++step) {
        double next_temp = alpha * current_temp + beta * control_signal;
        cout << "Шаг времени " << step << ": Температура = " << next_temp << std::endl;
        current_temp = next_temp; 
    }
}

void runNonlinearSimulation(double alpha, double beta, double gamma, double delta, double temp0, double control0, int steps_count) {
    double prev_temp = temp0; 
    double current_temp = temp0; 
    double control_signal = control0; 

    cout << "\nНелинейная модель:\n";
    for (int step = 0; step < steps_count; ++step) {
        double next_temp = alpha * current_temp - beta * prev_temp * prev_temp + gamma * control_signal + delta * sin(control_signal);
        cout << "Шаг времени " << step << ": Температура = " << next_temp << std::endl;
        prev_temp = current_temp; 
        current_temp = next_temp; 
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    double alpha, beta, gamma, delta;
    double start_temp, start_control;
    int steps_count;

    cout << "Введите значение параметра alpha: ";
    cin >> alpha;

    cout << "Введите значение параметра beta: ";
    cin >> beta;

    cout << "Введите значение параметра gamma (для нелинейной модели): ";
    cin >> gamma;

    cout << "Введите значение параметра delta (для нелинейной модели): ";
    cin >> delta;

    cout << "Введите начальное значение температуры temp0: ";
    cin >> start_temp;

    cout << "Введите начальное значение управляющего сигнала control0: ";
    cin >> start_control;

    cout << "Введите количество шагов моделирования: ";
    cin >> steps_count;

    runLinearSimulation(alpha, beta, start_temp, start_control, steps_count);
    runNonlinearSimulation(alpha, beta, gamma, delta, start_temp, start_control, steps_count);

    return 0;
}
```     
```
Введите значение параметра alpha: 1.2
Введите значение параметра beta: 0.05
Введите значение параметра gamma (для нелинейной модели): 0.4
Введите значение параметра delta (для нелинейной модели): 0.8
Введите начальное значение температуры temp0: 1
Введите начальное значение управляющего сигнала control0: 1
Введите количество шагов моделирования: 11
Линейная модель:
Шаг времени 0: Температура = 1.25
Шаг времени 1: Температура = 1.55
Шаг времени 2: Температура = 1.91
Шаг времени 3: Температура = 2.342
Шаг времени 4: Температура = 2.8604
Шаг времени 5: Температура = 3.48248
Шаг времени 6: Температура = 4.22898
Шаг времени 7: Температура = 5.12477
Шаг времени 8: Температура = 6.19973
Шаг времени 9: Температура = 7.48967
Шаг времени 10: Температура = 9.0376

Нелинейная модель:
Шаг времени 0: Температура = 2.22318
Шаг времени 1: Температура = 3.69099
Шаг времени 2: Температура = 5.25524
Шаг времени 3: Температура = 6.69829
Шаг времени 4: Температура = 7.73025
Шаг времени 5: Температура = 8.10612
Шаг времени 6: Температура = 7.81268
Шаг времени 7: Температура = 7.16294
Шаг времени 8: Температура = 6.6168
Шаг времени 9: Температура = 6.44795
Шаг времени 10: Температура = 6.62162
```
![График](./graphics.png)
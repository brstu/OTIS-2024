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
<p align="right">Рудь В. В.</p>
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

int main() {
    setlocale(LC_ALL, "RUS");

    double coeff_a = 1.0,
        coeff_b = 0.5,
        coeff_c = 0.1,
        coeff_d = 0.9,
        input_u = 1.5;

    double initial_temp = 0, current_nonlinear_temp = 0, previous_nonlinear_temp = 0;
    bool first_iteration = true; // используется для определения первой итерации

    cout << "Введите начальную температуру: ";
    cin >> initial_temp;

    current_nonlinear_temp = initial_temp;
    int iterations = 10;

    cout << "Линейная модель:" << endl;
    for (int i = 0; i < iterations; i++) {
        initial_temp = coeff_a * initial_temp + coeff_b * input_u;
        cout << "=" << initial_temp << endl;
    }

    cout << "Нелинейная модель:" << endl;
    for (int i = 0; i < iterations; i++) {
        if (first_iteration) {
            previous_nonlinear_temp = current_nonlinear_temp;
            current_nonlinear_temp = coeff_a * current_nonlinear_temp + coeff_c * input_u + coeff_d * sin(input_u);
            first_iteration = false; // первая итерация завершена
            cout << "=" << current_nonlinear_temp << endl;
        }
        else {
            double new_value = coeff_a * current_nonlinear_temp - coeff_b * pow(previous_nonlinear_temp, 2) + coeff_c * input_u + coeff_d * sin(input_u);
            previous_nonlinear_temp = current_nonlinear_temp; // обновляем предыдущее значение
            current_nonlinear_temp = new_value; // обновляем текущее значение
            cout << "=" << current_nonlinear_temp << endl;
        }
    }

    return 0;
}

```     
```
Вывод программы:
Введите начальную температуру: 0
Линейная модель:
=0.75
=1.5
=2.25
=3
=3.75
=4.5
=5.25
=6
=6.75
=7.5
Нелинейная модель:
=1.04775
=2.09549
=2.59435
=1.44656
=-0.871028
=-0.869544
=-0.201143
=0.468549
=1.49607
=2.43404
![График](./graphics.png)

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
<p align="right">Группы ИИ-26</p>
<p align="right">Шоева Е.Т..</p>
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
#include <vector>
#include <cmath>

class TemperatureControl {
public:
    TemperatureControl(double a, double b, double c, double d, double initialY0, double roomTemp)
        : a(a), b(b), c(c), d(d), Y0(roomTemp) {
        y.push_back(initialY0); 
        y_previous.push_back(initialY0); 
    }

    void simulate(int steps, double inputWarm) {
        for (int τ = 1; τ < steps; ++τ) {
            double y_current = a * y[τ - 1] + b * inputWarm; 
            double y_nonlinear = a * y[τ - 1] - b * std::pow(y_previous[τ - 1], 2) + c * inputWarm + d * std::sin(inputWarm);

            y.push_back(y_current); 
            y_previous.push_back(y[τ - 1]); 

            std::cout << "Шаг " << τ << ":\n";
            std::cout << "Линейная модель температуры: " << y_current << "\n";
            std::cout << "Нелинейная модель температуры: " << y_nonlinear << "\n\n";
        }
    }

private:
    double a, b, c, d; 
    double Y0; 
    std::vector<double> y; 
    std::vector<double> y_previous; 
};

int main() {
    setlocale(LC_ALL, "RU");
    
    double a = 0.9;
    double b = 0.5; 
    double c = 0.1;
    double d = 0.05; 
    double initialY0 = 20.0; 
    double roomTemp = 22.0; 
    double inputWarm = 5.0; 
    int steps = 10;

    TemperatureControl simulator(a, b, c, d, initialY0, roomTemp);
    simulator.simulate(steps, inputWarm);

    return 0;
}
```     
```
Вывод программы:
Шаг 1:
Линейная модель температуры: 20.5
Нелинейная модель температуры: -181.548

Шаг 2:
Линейная модель температуры: 20.95
Нелинейная модель температуры: -181.098

Шаг 3:
Линейная модель температуры: 21.355
Нелинейная модель температуры: -190.818

Шаг 4:
Линейная модель температуры: 21.7195
Нелинейная модель температуры: -199.78

Шаг 5:
Линейная модель температуры: 22.0476
Нелинейная модель температуры: -208.018

Шаг 6:
Линейная модель температуры: 22.3428
Нелинейная модель температуры: -215.573

Шаг 7:
Линейная модель температуры: 22.6085
Нелинейная модель температуры: -222.487

Шаг 8:
Линейная модель температуры: 22.8477
Нелинейная модель температуры: -228.801

Шаг 9:
Линейная модель температуры: 23.0629
Нелинейная модель температуры: -234.558
```
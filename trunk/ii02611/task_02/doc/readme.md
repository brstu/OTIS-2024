<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Прокопюк А.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

float a = 0.6, b = 0.8, c = 0.2, d = 1.0, e = 0.2;

float K = 0.9;
float time0 = 0.5, tc = 1.0, td = 0.5;
float output = 10;

float
q0 = K * (1 + (td / time0)),
q1 = -K * (1 + 2 * (td / time0) - (time0 / tc)),
q2 = K * (td / time0);

void nonlinear() {
    const short int init = 2;
    std::vector<float> res = { init, init };
    std::vector<double> err = { output - init, output - init };
    double ctrl_signal = 1;
    std::vector<double> ctrl = { ctrl_signal,ctrl_signal };

    while (abs(output - res.back()) > 1) {
        err.push_back(output - res.back());
        ctrl_signal = ctrl.back() + q0 * err.back() + q1 * err[err.size() - 2] + q2 * err[err.size() - 3];
        res.push_back(a * res.back() - b * res[res.size()-2] + c * ctrl_signal + d * sin(ctrl.back()));
        ctrl.push_back(ctrl_signal);
    }

    std::cout << std::right << std::setw(10) << "It" << std::setw(10) << std::right << "Output" << std::setw(13) << std::right << "Error" 
    << std::setw(13) << std::right << "Control" << std::endl;

    for (int i = 0; i < res.size(); i++) {
        std::cout << std::right << std::setw(10) << i+1 << std::setw(10) << res[i] << std::setw(13) << err[i] << std::setw(13) << ctrl[i] << std::endl;
    }}

int main() {  
    nonlinear();
    return 0;
}
'''
Вывод:
'''
        It    Output        Error      Control
         1         2            8            1
         2         2            8            1
         3   1.36147            8          4.6
         4 0.0930618      8.63853      9.34935
         5   2.03105      9.90694      14.9451
         6    4.7898      7.96895      14.7733
         7   5.08098       5.2102      15.1378
         8   3.64476      4.91902      19.4411
         9   3.58013      6.35524       24.502
        10    3.8796      6.41987      26.1855
        11   6.02793       6.1204      28.4773
        12   5.83833      3.97207       27.634
        13   5.61737      4.16167      31.6962
        14   5.73557      4.38263       33.796
        15   6.70876      4.26443      35.3566
        16   5.84614      3.29124      35.6302
        17   5.17016      4.15386      39.5399
        18   7.75887      4.82984      41.8495
        19   7.42397      2.24113      38.7549
        20   7.65678      2.57603       42.696
        21   6.32205      2.34322      43.1348
        22   6.27844      3.67795      46.8013
        23   8.49319      3.72156      47.3336
'''
![График](./graphic.png)
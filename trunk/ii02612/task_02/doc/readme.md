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

// Коэффициенты системы
double const a = 0.9;
double const b = 0.3;
double const c = 0.4;
double const d = 0.1;


// Параметры системы
double trans_coeff_K = 0.9;
double time0 = 0.5, timeC = 1.0, timeD = 0.5;
double req_output = 20;

// Параметры регулятора
double
par1 = trans_coeff_K * (1 + (timeD / time0)),
par2 = -trans_coeff_K * (1 + 2 * (timeD / time0) - (time0 / timeC)),
par3 = trans_coeff_K * (timeD / time0);


void NonlinearMod() {
    //Стартовые значения
    const short int init = 2;
    std::vector<double> nonlinearResult = {init, init}; // Вектор результатовм модели
    std::vector<double> err = {req_output-init, req_output - init}; // Вектор полученных ошибок
    double ctrl_signal = 1;
    std::vector<double> ctrl = { ctrl_signal,ctrl_signal}; // Вектор контрольных сигналов


    while (abs(req_output-nonlinearResult.back())>0.01) {
        err.push_back(req_output - nonlinearResult.back()); // Обновление ошибки
        ctrl_signal = ctrl.back() + par1 * err.back() + par2 * err[err.size() - 2] + par3 * err[err.size() - 3];
        nonlinearResult.push_back(a * nonlinearResult.back() - b * nonlinearResult[nonlinearResult.size()-2] + c * ctrl_signal + d * sin(ctrl.back()));
        ctrl.push_back(ctrl_signal);
    }

    std::cout << std::right << std::setw(10) << "Итерация"
        << std::setw(10) << std::right << "Вывод"
        << std::setw(13) << std::right << "Ошибка" 
        << std::setw(13) << std::right << "Контроль" << std::endl;

    for (int i = 0; i < nonlinearResult.size(); i++) {
        std::cout << std::right << std::setw(10) << i+1
            << std::setw(10) << nonlinearResult[i]
            << std::setw(13) << err[i]
            << std::setw(13) << ctrl[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    NonlinearMod();
    return 0;
}
'''
Вывод:
'''
  Итерация     Вывод       Ошибка     Контроль
         1         2           18            1
         2         2           18            1
         3   4.92415           18          9.1
         4   8.63826      15.0759      11.9365
         5   12.1051      11.3617       14.667
         6   15.1423      7.89491      16.8822
         7   17.1395      4.85773      18.0881
         8   18.5789      2.86047      19.4125
         9   19.5951       1.4211      19.9064
        10   20.1539      0.40493      20.0122
        11    20.393    -0.153853      20.1032
        12   20.4451    -0.392998      20.1064
        13   20.3982    -0.445103       20.051
        14   20.3109    -0.398191       19.982
        15    20.218    -0.310898      19.9177
        16   20.1372    -0.217987      19.8665
        17   20.0752     -0.13715      19.8303
        18   20.0326   -0.0752056      19.8073
        19   20.0063   -0.0325586      19.7945
'''
![График](./otis.png)
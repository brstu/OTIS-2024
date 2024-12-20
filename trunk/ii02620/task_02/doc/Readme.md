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
<p align="right">Хитренко А. А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №2 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>
#include <vector> 

using namespace std;

void control() {
    const double kp = 0.097;     
    const double ti = 2.162;  
    const double td = 1.0;         
    const double dt = 0.0001;     

    const double k0 = kp * (1.0 + (dt != 0 ? td / dt : 0.0));
    const double k1 = -kp * (1.0 + 2.0 * td / dt - dt / ti);
    const double k2 = (kp * td) / dt;

    const int numIter = 10;       
    const double setpoint = 29.0;    

    cout << "Начало работы регулятора\n";
    cout << setw(8) << "Итерация" << setw(20) << "Обновленное значение" << setw(20) << "Управляющее воздействие" << endl;

    const double a_model = 0.7;
    const double b_model = 0.2;
    double output = 0.0;
    double control = 0.0;


    auto model = [&](double e, double a, double b, double x) {
        return a * e + b * x; 
        };

    // Вектор для хранения значений ошибки
    vector<double> error(3, 0.0);

    // Цикл регулирования
    for (int i = 1; i <= numIter; i++) {
        error[2] = error[1];
        error[1] = abs(setpoint - output);
        const double deltaControl = k0 * error[1] + k1 * error[2] + k2 * error[0]; // Изменение управляющего воздействия
        const double prevControl = control;
        control = prevControl + deltaControl;
        output = model(output, a_model, b_model, control); 

        // Вывод результатов в таблицу
        cout << setw(8) << i << setw(22) << output << setw(20) << control << endl;
        error[0] = error[1]; //Обновление массива ошибок
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    control();
    return 0;
}



```     
```
Начало работы регулятора
Итерация   Выходное значениеУправляющее воздействие
       1               5626.56             28132.8
       2           1.08997e+06         5.43018e+06
       3           2.12234e+08         1.05735e+09
       4            4.1326e+10         2.05887e+11
       5           8.04697e+12         4.00902e+13
       6            1.5669e+15         7.80634e+15
       7           3.05106e+17         1.52005e+18
       8           5.94101e+19         2.95982e+20
       9           1.15683e+22         5.76335e+22
      10           2.25257e+24         1.12224e+25
![График](graphik.png)
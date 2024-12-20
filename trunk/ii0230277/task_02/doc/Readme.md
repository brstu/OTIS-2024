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
<p align="right">Группы ИИ-25</p>
<p align="right">Бекназарова А. С.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №2 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02702**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.
---
# Код программы: #
```C++
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double a, b, c, d;
double gain, time_const_0, time_delay, time_const, desired_output;
double reg0, reg1, reg2;

void nonlinear_system() {
    const short int initial_output = 2;
    double output[1000] = { initial_output, initial_output };
    double control_signal = 1.0;
    double error[1000] = { desired_output - initial_output, desired_output - initial_output };
    double previous_control_signal[1000] = { control_signal, control_signal };

    int i = 1;

    while (abs(desired_output - output[i]) > 0.01 && i < 1000) {
        error[i + 1] = desired_output - output[i];
        control_signal = previous_control_signal[i] + reg0 * error[i + 1] + reg1 * error[i] + reg2 * error[i - 1];

        output[i + 1] = a * output[i] - b * output[i - 1] + c * control_signal + d * sin(previous_control_signal[i]);
        previous_control_signal[i + 1] = control_signal;
        i++;
    }

    cout << setw(5) << setfill(' ') << "Шаг" << setw(10) << setfill(' ') << "Выход" << setw(12) << setfill(' ') << "Ошибка" << setw(20) << setfill(' ') << "Контрольный сигнал" << endl;
    for (int j = 0; j <= i; j++) {
        cout << setw(5) << setfill(' ') << j + 1;
        cout << setw(12) << setfill(' ') << output[j];
        cout << setw(15) << setfill(' ') << error[j];
        cout << setw(20) << setfill(' ') << previous_control_signal[j] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Введите коэффициенты системы: " << endl;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;
    cout << "d: ";
    cin >> d;

    cout << "Введите параметры системы:\n";
    cout << "Прирост: ";
    cin >> gain;
    cout << "Временная константа: ";
    cin >> time_const_0;
    cout << "Задержка времени: ";
    cin >> time_delay;
    cout << "Вторая временная константа: ";
    cin >> time_const;
    cout << "Желаемое значение выхода: ";
    cin >> desired_output;

    reg0 = gain * (1 + (time_delay / time_const_0));
    reg1 = -gain * (1 + 2 * (time_delay / time_const_0) - (time_const_0 / time_const));
    reg2 = gain * (time_delay / time_const_0);

    nonlinear_system();

    return 0;
}
```     
Вывод программы: 
```
Введите коэффициенты системы:
a: 0.4
b: 0.8
c: 0.8
d: 0.7
Введите параметры системы:
Прирост: 0.9
Временная константа: 1
Задержка времени: 1.2
Вторая временная константа: 1
Желаемое значение выхода: 20
  Шаг     Выход      Ошибка  Контрольный сигнал
    1           2             18                   1
    2           2             18                   1
    3      13.549             18                17.2
    4     11.5481        6.45097             10.5329
    5     19.3725        8.45188             32.7736
    6     17.3763       0.627546             22.7271
    7     19.5383         2.6237             35.6945
    8     18.5745       0.461711             31.6193
    9      20.963        1.42547              36.278
   10     18.2662      -0.962955              31.791
   11     21.8673        1.73382             38.8434
   12     19.0602        -1.8673             30.3611
   13     20.0237       0.939798             38.1278
   14     20.2798     -0.0236628             34.0343
   15     20.0799      -0.279781             34.5465
   16     19.7895     -0.0799028              34.967
   17     19.7766       0.210503             35.2543
   18     19.7544       0.223433             35.1557
   19     19.9957       0.245635             35.3868
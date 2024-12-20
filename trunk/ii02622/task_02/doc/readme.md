<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Цурукова В.А.</p>
<p align="right">Проверила:</p>
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
#include <vector>
#include <cmath>
#include <iomanip>  // Для форматирования вывода
using namespace std;

// Коэффициенты системы
double system_a, system_b, system_c, system_d;
// Параметры системы
double gain_factor, t_const_0, t_delay, t_const, target_output;
// Параметры регулятора
double regulator_0, regulator_1, regulator_2;

void run_simulation() {
    const double initial_value = 2.0;  // Начальное значение выхода
    double control_value = 1.0;        // Управляющий сигнал
    vector<double> outputs = { initial_value };  // Вектор выходных значений
    vector<double> errors = { target_output - initial_value };  // Вектор ошибок
    vector<double> controls = { control_value };  // История управляющего сигнала

    // Цикл продолжается, пока ошибка не станет меньше 0.01
    while (fabs(errors.back()) > 0.01) {
        // Вычисление новой ошибки
        errors.push_back(target_output - outputs.back());

        // Вычисление нового управляющего сигнала
        control_value = controls.back()
            + regulator_0 * errors.back()
            + regulator_1 * (errors.size() > 1 ? errors[errors.size() - 2] : 0.0)
            + regulator_2 * (errors.size() > 2 ? errors[errors.size() - 3] : 0.0);

        // Обновление выходного значения системы
        double next_output = system_a * outputs.back()
            - system_b * (outputs.size() > 1 ? outputs[outputs.size() - 2] : 0.0)
            + system_c * control_value
            + system_d * sin(controls.back());

        outputs.push_back(next_output);  // Добавляем новое значение в вектор выходов
        controls.push_back(control_value);  // Сохраняем управляющий сигнал
    }

    // Вывод результатов
    cout << fixed << setprecision(4);  // Форматирование вывода с 4 знаками после запятой
    cout << "Step\tOutput\tError\tControl Signal\n";
    for (size_t i = 0; i < outputs.size(); ++i) {
        cout << i + 1 << "\t"
            << outputs[i] << "\t"
            << errors[i] << "\t"
            << controls[i] << endl;
    }
}

int main() {
    // Ввод параметров системы
    setlocale(LC_ALL, "RU");
    cout << "Введите коэффициенты системы:\n";
    cout << "system_a: "; cin >> system_a;
    cout << "system_b: "; cin >> system_b;
    cout << "system_c: "; cin >> system_c;
    cout << "system_d: "; cin >> system_d;

    cout << "\nВведите параметры системы:\n";
    cout << "gain_factor: "; cin >> gain_factor;
    cout << "t_const_0: "; cin >> t_const_0;
    cout << "t_delay: "; cin >> t_delay;
    cout << "t_const: "; cin >> t_const;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    // Расчет параметров регулятора
    regulator_0 = gain_factor * (1 + (t_delay / t_const_0));
    regulator_1 = -gain_factor * (1 + 2 * (t_delay / t_const_0) - (t_const_0 / t_const));
    regulator_2 = gain_factor * (t_delay / t_const_0);

    // Запуск симуляции системы
    run_simulation();

    return 0;
}
'''
Вывод:
'''
 Введите коэффициенты системы:
system_a: 0.9
system_b: 0.3
system_c: 0.4
system_d: 0.1

Введите параметры системы:
gain_factor: 0.9
t_const_0: 0.5
t_delay: 0.5
t_const: 1.0
target_output (желаемое значение выхода): 20
Step    Output  Error   Control Signal
1       2.0000  18.0000 1.0000
2       -0.9559 18.0000 -7.1000
3       0.9950  20.9559 6.3205
4       5.0175  19.0050 9.5788
5       9.2605  14.9825 12.6463
6       12.9857 10.7395 15.3714
7       15.8690 7.0143  17.3174
8       17.7411 4.1310  18.6367
9       19.0735 2.2589  19.7207
10      19.9299 0.9265  20.0239
11      20.3465 0.0701  20.0985
12      20.4881 -0.3465 20.1509
13      20.4777 -0.4881 20.1150
14      20.3955 -0.4777 20.0415
15      20.2916 -0.3955 19.9652
16      20.1937 -0.2916 19.9002
17      20.1143 -0.1937 19.8517
18      20.0568 -0.1143 19.8193
19      20.0193 -0.0568 19.8000
20      19.9978 -0.0193 19.7902
21      19.9876 0.0022  19.7865
'''
![График](./otis.png)
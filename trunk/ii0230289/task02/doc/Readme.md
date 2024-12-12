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
<p align="right">Милевский А.Д.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.

# Задание #
На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double system_coeff_a, system_coeff_b, system_coeff_c, system_coeff_d; // Коэффициенты системы
double system_gain, time_constant_0, system_delay, time_constant, target_output; // Параметры системы
double controller_k0, controller_k1, controller_k2; // Параметры регулятора
void run_simulation() {
    const double initial_value = 2.0; // Начальное значение выхода
    double control_signal = 1.0;      // Управляющий сигнал

    vector<double> outputs = { initial_value }; // Вектор выходных значений
    vector<double> errors = { target_output - initial_value }; // Вектор ошибок
    vector<double> control_signals = { control_signal }; // История управляющего сигнала

    while (fabs(errors.back()) > 0.01) {
        // Вычисляем текущую ошибку
        errors.push_back(target_output - outputs.back());

        // Вычисляем новый управляющий сигнал
        control_signal = control_signals.back()
            + controller_k0 * errors.back()
            + controller_k1 * (errors.size() > 1 ? errors[errors.size() - 2] : 0)
            + controller_k2 * (errors.size() > 2 ? errors[errors.size() - 3] : 0);

        // Обновляем выход системы
        double new_output = system_coeff_a * outputs.back()
            - system_coeff_b * (outputs.size() > 1 ? outputs[outputs.size() - 2] : 0)
            + system_coeff_c * control_signal
            + system_coeff_d * sin(control_signals.back());
        outputs.push_back(new_output);
        control_signals.push_back(control_signal);
    }
    cout << fixed << setprecision(4);
    cout << "Step\tOutput\t\tError\t\tControl Signal\n";
    for (size_t i = 0; i < outputs.size(); ++i) {
        cout << i + 1 << "\t"
            << outputs[i] << "\t\t"
            << errors[i] << "\t\t"
            << (i < control_signals.size() ? control_signals[i] : 0) << endl;
    }
}

void initialize_parameters() {
    setlocale(LC_ALL, "RU");

    cout << "Введите коэффициенты системы:\n";
    cout << "system_coeff_a: "; cin >> system_coeff_a;
    cout << "system_coeff_b: "; cin >> system_coeff_b;
    cout << "system_coeff_c: "; cin >> system_coeff_c;
    cout << "system_coeff_d: "; cin >> system_coeff_d;

    cout << "\nВведите параметры системы:\n";
    cout << "system_gain: "; cin >> system_gain;
    cout << "time_constant_0: "; cin >> time_constant_0;
    cout << "system_delay: "; cin >> system_delay;
    cout << "time_constant: "; cin >> time_constant;
    cout << "target_output (желаемое значение выхода): "; cin >> target_output;

    controller_k0 = system_gain * (1 + (system_delay / time_constant_0));
    controller_k1 = -system_gain * (1 + 2 * (system_delay / time_constant_0) - (time_constant_0 / time_constant));
    controller_k2 = system_gain * (system_delay / time_constant_0);
}

int main() {
    initialize_parameters(); // Ввод параметров системы
    run_simulation();        // Запуск симуляции
    return 0;
}




```     

Вывод программы:

Введите коэффициенты системы:
system_coeff_a: 0.8
system_coeff_b: 0.4
system_coeff_c: 0.6
system_coeff_d: 0.7

Введите параметры системы:
system_gain: 0.9
time_constant_0: 1
system_delay: 1.2
time_constant: 1
target_output (желаемое значение выхода): 20
Step    Output          Error           Control Signal
1       2.0000          18.0000         1.0000
2       0.8450          18.0000         -2.2400
3       9.0751          19.1550         16.2468
4       16.1289         10.9249         15.9434
5       21.5285         3.8711          20.6978
6       24.1097         -1.5285         21.1087
7       23.4893         -4.1097         20.4538
8       22.3099         -3.4893         20.7713
9       20.6872         -2.3099         19.2960
10      19.4219         -0.6872         19.1564
11      19.0485         0.5781          19.2907
12      19.2792         0.9515          19.1838
13      19.5416         0.7208          19.1801
14      19.8838         0.4584          19.5584
15      20.2921         0.1162          19.5768
16      20.2910         -0.2921         19.2425
17      20.0376         -0.2910         19.4227
18      20.0901         -0.0376         19.6614
19      20.1148         -0.0901         19.2499
20      19.8345         -0.1148         19.1765
21      19.8394         0.1655          19.6549
22      20.1373         0.1606          19.4914
23      20.0240         -0.1373         19.0514
24      19.7890         -0.0240         19.4739
25      20.1080         0.2110          19.7953
26      20.1983         -0.1080         19.0998
27      19.7898         -0.1983         19.1683
28      19.9096         0.2102          19.8963
29      20.2620         0.0904          19.4070
30      19.9681         -0.2620         18.9200
31      19.7070         0.0319          19.6468
32      20.2042         0.2930          19.8750
33      20.2024         -0.2042         18.8723
34      19.6336         -0.2024         19.2290
35      19.9879         0.3664          20.1712
36      20.3263         0.0121          19.1851
37      19.8415         -0.3263         18.9086
38      19.7481         0.1585          19.9402
39      20.3293         0.2519          19.7442
40      20.1418         -0.3293         18.7193
41      19.5440         -0.1418         19.4219
42      20.1229         0.4560          20.2755
43      20.3098         -0.1229         18.8940
44      19.6530         -0.3098         19.0385
45      19.8873         0.3470          20.2622
46      20.3806         0.1127          19.4012
47      19.9838         -0.3806         18.7789
48      19.6383         0.0162          19.7549
49      20.2827         0.3617          20.0250
50      20.2377         -0.2827         18.7014
51      19.5130         -0.2377         19.2321
52      20.0193         0.4870          20.4045
53      20.3447         -0.0193         19.0576
54      19.7783         -0.3447         18.9427
55      19.8132         0.2217          20.1055
56      20.3793         0.1868          19.6242
57      20.0933         -0.3793         18.7090
58      19.5521         -0.0933         19.5455
59      20.1876         0.4479          20.2241
60      20.2865         -0.1876         18.7844
61      19.5723         -0.2865         19.1062
62      19.9425         0.4277          20.3692
63      20.3741         0.0575          19.2499
64      19.9032         -0.3741         18.8469
65      19.7162         0.0968          19.9087
66      20.3365         0.2838          19.8574
67      20.1844         -0.3365         18.6828
68      19.5073         -0.1844         19.3511
69      20.0854         0.4927          20.3614
70      20.3215         -0.0854         18.9289
71      19.6838         -0.3215         19.0089
72      19.8718         0.3162          20.2371
73      20.3887         0.1282          19.4608
74      20.0174         -0.3887         18.7558
75      19.6125         -0.0174         19.6993
76      20.2594         0.3875          20.0844
77      20.2524         -0.2594         18.7149
78      19.5206         -0.2524         19.1941
79      19.9969         0.4794          20.4082
80      20.3530         0.0031          19.1063
![График :](graph.png)

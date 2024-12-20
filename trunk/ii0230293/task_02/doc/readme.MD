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
<p align="right">Подгайский Д. А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

1. Написать отчет по выполненной лабораторной работе №2 в .md формате (*readme.md*) и с помощью **pull request** разместить его в следующем каталоге: **trunk\ii0xxyy\task_02\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

**Задание.**
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <cmath>

using namespace std;

struct PIDParameters {
    double proportional_gain;
    double integral_gain;
    double derivative_gain;
    double coefficient_K;
    double time_constant_T;
    double derivative_time_TD;
    double sampling_interval_T0;
};

double computeControlSignal(double target, double current_value, double time_step, PIDParameters& pid_params, double& previous_error, double& integral_term) {
    double current_error = target - current_value;
    integral_term += current_error * time_step;
    double derivative_term = (current_error - previous_error) / time_step;

    double control_signal = pid_params.proportional_gain * current_error
        + pid_params.integral_gain * integral_term
        + pid_params.derivative_gain * derivative_term;

    previous_error = current_error;
    return control_signal;
}

int main() {
    PIDParameters params = { 1.0, 0.1, 0.05, 0.8, 100.0, 100.0, 1.1 };

    double target_value = 100.0;  // Целевая величина
    double current_value = 90.0; // Текущее значение
    double time_step = 0.1;      // Интервал времени
    double previous_error = 0.0; // Предыдущая ошибка
    double integral_term = 0.0;  // Интегральная составляющая

    for (int iteration = 0; iteration < 100; ++iteration) {
        double control_signal = computeControlSignal(target_value, current_value, time_step, params, previous_error, integral_term);

        cout << "Iteration " << iteration << ": Control Signal = " << control_signal << endl;

        current_value += control_signal * 0.1;
    }

    return 0;
}
```

Результат выполнения программы:

```
Iteration 0: Control Signal = 15.1
Iteration 1: Control Signal = 7.9199
Iteration 2: Control Signal = 7.5639
Iteration 3: Control Signal = 6.89472
Iteration 4: Control Signal = 6.30123
Iteration 5: Control Signal = 5.757
Iteration 6: Control Signal = 5.25898
Iteration 7: Control Signal = 4.80318
Iteration 8: Control Signal = 4.38606
Iteration 9: Control Signal = 4.00432
Iteration 10: Control Signal = 3.65499
Iteration 11: Control Signal = 3.33531
Iteration 12: Control Signal = 3.04278
Iteration 13: Control Signal = 2.77511
Iteration 14: Control Signal = 2.53019
Iteration 15: Control Signal = 2.30609
Iteration 16: Control Signal = 2.10105
Iteration 17: Control Signal = 1.91346
Iteration 18: Control Signal = 1.74185
Iteration 19: Control Signal = 1.58485
Iteration 20: Control Signal = 1.44124
Iteration 21: Control Signal = 1.30988
Iteration 22: Control Signal = 1.18973
Iteration 23: Control Signal = 1.07985
Iteration 24: Control Signal = 0.979366
Iteration 25: Control Signal = 0.887479
Iteration 26: Control Signal = 0.803463
Iteration 27: Control Signal = 0.726651
Iteration 28: Control Signal = 0.656434
Iteration 29: Control Signal = 0.592253
Iteration 30: Control Signal = 0.533595
Iteration 31: Control Signal = 0.479994
Iteration 32: Control Signal = 0.431019
Iteration 33: Control Signal = 0.38628
Iteration 34: Control Signal = 0.345417
Iteration 35: Control Signal = 0.308101
Iteration 36: Control Signal = 0.274031
Iteration 37: Control Signal = 0.242931
Iteration 38: Control Signal = 0.214551
Iteration 39: Control Signal = 0.188657
Iteration 40: Control Signal = 0.16504
Iteration 41: Control Signal = 0.143506
Iteration 42: Control Signal = 0.123878
Iteration 43: Control Signal = 0.105993
Iteration 44: Control Signal = 0.0897038
Iteration 45: Control Signal = 0.0748739
Iteration 46: Control Signal = 0.0613791
Iteration 47: Control Signal = 0.0491057
Iteration 48: Control Signal = 0.0379494
Iteration 49: Control Signal = 0.027815
Iteration 50: Control Signal = 0.0186151
Iteration 51: Control Signal = 0.0102698
Iteration 52: Control Signal = 0.00270608
Iteration 53: Control Signal = -0.00414307
Iteration 54: Control Signal = -0.0103389
Iteration 55: Control Signal = -0.0159374
Iteration 56: Control Signal = -0.0209901
Iteration 57: Control Signal = -0.0255438
Iteration 58: Control Signal = -0.0296415
Iteration 59: Control Signal = -0.0333226
Iteration 60: Control Signal = -0.0366231
Iteration 61: Control Signal = -0.0395759
Iteration 62: Control Signal = -0.0422113
Iteration 63: Control Signal = -0.0445568
Iteration 64: Control Signal = -0.0466377
Iteration 65: Control Signal = -0.0484771
Iteration 66: Control Signal = -0.0500961
Iteration 67: Control Signal = -0.0515142
Iteration 68: Control Signal = -0.052749
Iteration 69: Control Signal = -0.0538167
Iteration 70: Control Signal = -0.0547322
Iteration 71: Control Signal = -0.055509
Iteration 72: Control Signal = -0.0561596
Iteration 73: Control Signal = -0.0566952
Iteration 74: Control Signal = -0.0571264
Iteration 75: Control Signal = -0.0574625
Iteration 76: Control Signal = -0.0577123
Iteration 77: Control Signal = -0.0578838
Iteration 78: Control Signal = -0.0579841
Iteration 79: Control Signal = -0.0580199
Iteration 80: Control Signal = -0.0579974
Iteration 81: Control Signal = -0.0579221
Iteration 82: Control Signal = -0.057799
Iteration 83: Control Signal = -0.0576328
Iteration 84: Control Signal = -0.0574277
Iteration 85: Control Signal = -0.0571877
Iteration 86: Control Signal = -0.0569162
Iteration 87: Control Signal = -0.0566165
Iteration 88: Control Signal = -0.0562916
Iteration 89: Control Signal = -0.0559442
Iteration 90: Control Signal = -0.0555767
Iteration 91: Control Signal = -0.0551913
Iteration 92: Control Signal = -0.0547902
Iteration 93: Control Signal = -0.0543752
Iteration 94: Control Signal = -0.0539481
Iteration 95: Control Signal = -0.0535103
Iteration 96: Control Signal = -0.0530633
Iteration 97: Control Signal = -0.0526084
Iteration 98: Control Signal = -0.0521467
Iteration 99: Control Signal = -0.0516795
```
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
<p align="right">Котов В. В.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
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
#include <vector>
#include <fstream>

using namespace std;

const double K = 0.0001;
const double T = 100;
const double TD = 100;
const double T0 = 1;

const double q0 = K * (1 + TD / T0);
const double q1 = -K * (1 + 2 * TD / T0 - T0 / T);
const double q2 = K * TD / T0;


class func {
private:
    vector<double> q = { q0, q1, q2 };
    vector<double> e = { 0, 0, 0 };
    vector<double> y = { 0, 0, 0 };
    vector<double> u = { 1, 1 };

public:
    double summ() {
        double summ = 0;
        for (int i = 0; i < 3; i++) {
            summ += q[i] * e[i];
        }
        return summ;
    }

    void nonlinear(int time, double setp, double a = 0.5, double b = 0.3, double c = 0.9, double d = 0.7) {
        for (int i = 0; i < time; i++) {
            e[0] = setp - y[y.size() - 1];
            e[1] = setp - y[y.size() - 2];
            e[2] = setp - y[y.size() - 3];
            u[0] = u[1] + summ();
            y.push_back(a * y[y.size() - 1] - b * y[y.size() - 2] * y[y.size() - 2] + c * u[0] + d * sin(u[1]));
            u[1] = u[0];
        }
    }

    vector<double> getY() const {
        return y;
    }
};

int main() {
    double setp;
    ofstream out("output.txt");
    func f;

    if (out.is_open()) {
        cout << "Enter the setpoint: ";
        cin >> setp;
        f.nonlinear(100, setp);
        vector<double> y_values = f.getY();

        for (int i = 0; i < y_values.size(); i++) {
            double scaledValue = y_values[i] * setp / y_values[y_values.size() - 1];
            cout << i << " " << scaledValue << endl;
            out << i << " " << scaledValue << endl;
        }

        out.close();
    }
    else {
        cerr << "Error: Cannot open the output file." << endl;
    }

    return 0;
}

```

Результат выполнения программы:

```
15.1
7.9199
7.5639
6.89472
6.30123
5.757
5.25898
4.80318
4.38606
4.00432
3.65499
3.33531
3.04278
2.77511
2.53019
2.30609
2.10105
1.91346
1.74185
1.58485
1.44124
1.30988
1.18973
1.07985
0.979366
0.887479
0.803463
0.726651
0.656434
0.592253
0.533595
0.479994
0.431019
0.38628
0.345417
0.308101
0.274031
0.242931
0.214551
0.188657
0.16504
0.143506
0.123878
0.105993
0.0897038
0.0748739
0.0613791
0.0491057
0.0379494
0.027815
0.0186151
0.0102698
0.00270608
-0.00414307
-0.0103389
-0.0159374
-0.0209901
-0.0255438
-0.0296415
-0.0333226
-0.0366231
-0.0395759
-0.0422113
-0.0445568
-0.0466377
-0.0484771
-0.0500961
-0.0515142
-0.052749
-0.0538167
-0.0547322
-0.055509
-0.0561596
-0.0566952
-0.0571264
-0.0574625
-0.0577123
-0.0578838
-0.0579841
-0.0580199
-0.0579974
-0.0579221
-0.057799
-0.0576328
-0.0574277
-0.0571877
-0.0569162
-0.0566165
-0.0562916
-0.0559442
-0.0555767
-0.0551913
-0.0547902
-0.0543752
-0.0539481
-0.0535103
-0.0530633
-0.0526084
-0.0521467
-0.0516795
```
---

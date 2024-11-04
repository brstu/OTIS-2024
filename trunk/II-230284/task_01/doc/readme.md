<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
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
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>

using namespace std;

double line(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

double nonline(double y_prev, double y_prev_prev, double u, double a, double b, double c, double d) {
    return a * y_prev - b * pow(y_prev_prev, 2) + c * u + d * sin(u);
}

int main() {
    setlocale(LC_ALL, "Russian");
    double y = 4;
    double a = 0.7, b = 0.5, c = 0.5, d = 10;
    double u[15];
    for (int i = 0; i < 15; i++)
    {
        u[i] = i + 1;
    }
    cout << "Время\tЛинейная модель\t\t\tНелинейная модель" << endl;
    double y_prev_prev = 2;
    double y_nonlinear = y;
    for (int i = 0; i < 15; i++) {
        y = line(y, u[i], a, b);
        y_nonlinear = nonline(y_nonlinear, y_prev_prev, u[i], a, b, c, d);
        cout << i + 1 << "\t" << y << "\t\t\t\t" << y_nonlinear << endl;
    }
    return 0;
}
```

Результат выполнения программы:

```
Время   Линейная модель                 Нелинейная модель
1       3.3                             9.71471
2       3.31                            14.8933
3       3.817                           11.3365
4       4.6719                          0.367518
5       5.77033                         -8.83198
6       7.03923                         -7.97654
7       8.42746                         2.48629
8       9.89922                         13.634
9       11.4295                         16.165
10      13.0006                         8.87527
11      14.6004                         -0.287213
12      16.2203                         -1.56678
13      17.8542                         7.60493
14      19.4979                         20.2295
15      21.1486                         26.1635
```
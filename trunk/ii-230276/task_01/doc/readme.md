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
<p align="right">Бажежа А.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я.С.</p>
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

a$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

a$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
a$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# Выполнение задания #

Код программы:
```C++
#include <iostream>
using namespace std;

double linear_model(double y1, double u, double a, double b) 
{
    return a * y1 + b * u;
}

double nonlinear_model(double y1, double y0, double u,
    double a, double b, double c, double d) 
{
    return a * y1 - b * pow(y0, 2) + c * u + d * sin(u);
}

int main() {
    double y = 3, a = 0.8, b = 0.5, c = 0.8, d = 10;
    double y0 = 2, y_non = y;
    double u[10];
    for (int i = 0; i < 10; i++)
    {
        u[i] = i + 0.5;
    }
    cout << "Time\t\tLinear model\t\tNonlinear model" << endl;
    for (int i = 0; i < 10; i++) {
        y = linear_model(y, u[i], a, b);
        y_non = nonlinear_model(y_non, y0, u[i], a, b, c, d);
        cout << i + 1 << "\t\t" << y << "\t\t\t" << y_non << endl;
    }
    return 0;
}
```

Результат выполнения программы:

```
Time            Linear model            Nonlinear model
1               2.65                    5.59426
2               2.87                    13.6504
3               3.546                   16.905
4               4.5868                  10.8162
5               5.91944                 0.477636
6               7.48555                 -4.27329
7               9.23844                 1.93256
8               11.1408                 14.9261
9               13.1626                 24.7257
10              15.2801                 24.6291
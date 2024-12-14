<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Жук Б.Д.</p>
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

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.
---
# Код программы: #
```C++    
#include <iostream>
#include <cmath>
#include <string>

static double a = 0.5;
static double b = 0.01;
static double c = 0.2;
static double d = 0.4;

double Linear(double y, double u) {
    return a * y + b * u;
}

double Nonlinear(double y, double u, double y_prev, double u_prev) {
    return a * y - b * pow(y_prev, 2) + c * u + d * sin(u_prev);
}

int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "Введите начальную температуру:" << std::endl;
    double y;
    std::cin >> y;
    double y_next = y;
    double y_prev;
    double u = 8;
    double u_prev = u;
    int steps = 20;

    std::cout << "Линейная модель" << std::endl;
    std::cout << "Время:\tТемпература:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_prev = y_next;
        y_next = Linear(y_next, u);
        std::cout << (i + 1) << "\t" << y_next << std::endl;
    }

    std::cout << std::endl;
    y_next = y;
    std::cout << "Нелинейная модель" << std::endl;
    std::cout << "Время:\tТемпература:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_prev = y_next;
        y_next = Nonlinear(y_next, u, y, u_prev);
        std::cout << (i + 1) << "\t" << y_next << std::endl;
    }

    return 0;
}


```
Результат:
```
Введите начальную температуру:
15
Линейная модель
Время:  Температура:
1       7.58
2       3.87
3       2.015
4       1.0875
5       0.62375
6       0.391875
7       0.275938
8       0.217969
9       0.188984
10      0.174492
11      0.167246
12      0.163623
13      0.161812
14      0.160906
15      0.160453
16      0.160226
17      0.160113
18      0.160057
19      0.160028
20      0.160014

Нелинейная модель
Время:  Температура:
1       7.24574
2       3.36861
3       1.43005
4       0.460769
5       -0.0238724
6       -0.266193
7       -0.387353
8       -0.447933
9       -0.478223
10      -0.493368
11      -0.500941
12      -0.504727
13      -0.50662
14      -0.507567
15      -0.50804
16      -0.508277
17      -0.508395
18      -0.508454
19      -0.508484
20      -0.508499
```
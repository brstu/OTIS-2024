<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Елец Ю.А.</p>
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
using namespace std;

double a = 0.5;  
double b = 0.01;   
double c = 0.2;  
double d = 0.4;  

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double u, double y_pred, double u_pred) {
    return a * y - b * pow(y_pred, 2) + c * u + d * sin(u_pred);
}
  
int main() {
    setlocale(LC_ALL, "ru");
    double y;
    cout << "Введите начальную температуру:" << endl;
    cin >> y;
    double y_next = y;
    double y_pred;
    double u = 8;
    double u_pred;
    u_pred = u;
    int steps = 10;

    cout << "Линейная модель" << endl;
    cout << "Время:\tТемпература:" << endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        y_next = linearModel(y_next, u);
        cout << i + 1 << "\t" << y_next << endl;
    }
    cout << endl;
    y_next = y;
    cout << "Нелинейная модель:" << endl;
    cout << "Время:\tТемпература:" << endl;
    for (int i = 0; i < steps; i++) {
        y_pred = y_next;
        y_next = nonlinearModel(y_next, u, y, u_pred);
        cout << i + 1 << "\t" << y_next << endl; 
    }
    return 0;
}
```
Результат:
```
Введите начальную температуру:
10
Линейная модель
Время:  Температура:
1       5.08
2       2.62
3       1.39
4       0.775
5       0.4675
6       0.31375
7       0.236875
8       0.198437
9       0.179219
10      0.169609

Нелинейная модель:
Время:  Температура:
1       5.99574
2       3.99361
3       2.99255
4       2.49202
5       2.24175
6       2.11662
7       2.05405
8       2.02277
9       2.00713
10      1.99931
```
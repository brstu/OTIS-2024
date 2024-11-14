<p align="center"> ������������ ����������� ���������� ��������</p>
<p align="center">���������� �����������</p>
<p align="center">���������� ��������������� ����������� �����������</p>
<p align="center">������� ���</p>
<br><br><br><br><br><br><br>
<p align="center">������������ ������ �1</p>
<p align="center">�� ���������� ������ ������ ���������������� ������</p>
<p align="center">����: �������������� ����������� ��������</p>
<br><br><br><br><br>
<p align="right">��������:</p>
<p align="right">������� 2 �����</p>
<p align="right">������ ��-26</p>
<p align="right">����� �. �.</p>
<p align="right">���������:</p>
<p align="right">�������� �. �.</p>
<br><br><br><br><br>
<p align="center">����� 2024</p>

<hr>

# ����� ������� #
1. �������� ����� �� ����������� ������������ ������ �1 � .md ������� (readme.md) � � ������� ������� �� �������� ��������� (**pull request**) ���������� ��� � ��������� ��������: **trunk\ii0xxyy\task_01\doc** (��� **xx** - ����� ������, **yy** - ����� ��������, �������� **ii02102**).
2. �������� ��� ���������� ��������� ���������� � ��������: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ � time; $y(\tau)$ � input temperature; $u(\tau)$ � input warm; $Y_0$ � room temperature; $C,RC$ � some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ � time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ � some constants.

Task is to write program (**�++**), which simulates this object temperature.

<hr>

# ���������� ������� #

��� ���������:
```C++
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double alfa = 0.6; 
const double beta = 0.2; 
const double gamma = 0.01;
const double delta = 0.4; 


double rpex(double u_prev) {
    return exp(-u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 9; 
    double y_0 = 10; 
    double u_0 = 10; 
    vector<double> y_linear(n + 1, y_0);
    vector<double> y_nonlinear(n + 1, y_0);

    
    for (int t = 0; t < n; ++t) {
        // �������� ������
        y_linear[t + 1] = alfa * y_linear[t] + beta * u_0;

        // ���������� ������
        double u_prev = (t > 0) ? u_0 : 0.0; 
        y_nonlinear[t + 1] = alfa * y_nonlinear[t] - beta * pow(y_nonlinear[t], 2) + gamma * u_0 + delta * rpex(u_prev);
    }

    
    cout << "��������� ���\t�������� ������\t���������� ������\n";
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t\t" << y_linear[t] << "\t\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
```     
```
��������� ���   �������� ������ ���������� ������
0               10              10
1               8               -13.5
2               6.8             -44.45
3               6.08            -421.73
4               5.648           -35824.2
5               5.3888          -2.56696e+08
6               5.23328         -1.31786e+16
7               5.13997         -3.4735e+31
8               5.08398         -2.41304e+62
9               5.05039         -1.16456e+124

![������](image.png)
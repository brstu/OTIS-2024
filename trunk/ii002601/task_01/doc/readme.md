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
<p align="right">����� �.�.</p>
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
#include <cmath>
#include <vector>

using namespace std;

const double coefficients[] = { 0.8, 0.6, 0.4, 2.2 }; // ������������ ��� �������������
const double u = 0.8;

// ������� ��� ������� �������� ������
vector<double> calculateLinearModel(int steps, double initialTemperature) {
    vector<double> results(steps);
    results[0] = initialTemperature; // ������������� ��������� ��������

    for (int t = 1; t < steps; ++t) {
        results[t] = coefficients[0] * results[t - 1] + coefficients[1] * u; // ������� �������� ������
    }
    return results;
}

// ������� ��� ������� ���������� ������
vector<double> calculateNonlinearModel(int steps, double initialTemperature) {
    vector<double> results(steps);
    results[0] = initialTemperature; // ������������� ��������� ��������

    if (steps > 1) {
        results[1] = coefficients[0] * results[0] + coefficients[2] * u + coefficients[3] * sin(u); // ��������� y1 ��� ������� ����
    }

    for (int t = 2; t < steps; ++t) {
        results[t] = coefficients[0] * results[t - 1] - coefficients[1] * pow(results[t - 2], 2)
            + coefficients[2] * u + coefficients[3] * sin(u); // ������� ���������� ������
    }
    return results;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double initialTemperature; // ���������� ��� ��������� �����������
    int steps; // ���������� ��� ���������� �����

    // ���� ������
    cout << "����� ���������� � ��������� �������������!\n";
    cout << "����������, ������� ��������� �����������: ";
    cin >> initialTemperature;

    cout << "������� ���������� ����� (����� ������������� �����): ";
    cin >> steps;

    // �������� �� ������������ ����� ���������� �����
    while (steps <= 0) {
        cout << "���������� ����� ������ ���� �������������. ���������� �����: ";
        cin >> steps;
    }

    // ������ �����������
    vector<double> linearResults = calculateLinearModel(steps + 1, initialTemperature);
    vector<double> nonlinearResults = calculateNonlinearModel(steps + 1, initialTemperature);

    // ����� ����������� ��� �������� ������
    cout << "\n--- ���������� �������� ������ ---\n";
    for (int t = 0; t <= steps; ++t) {
        cout << "��� " << t << ": " << linearResults[t] << "\n";
    }

    // ����� ����������� ��� ���������� ������
    cout << "\n--- ���������� ���������� ������ ---\n";
    for (int t = 0; t <= steps; ++t) {
        cout << "��� " << t << ": " << nonlinearResults[t] << "\n";
    }

    return 0;
}
```     
```
����� ���������� � ��������� �������������!
����������, ������� ��������� �����������: 25
������� ���������� ����� (����� ������������� �����): 10

--- ���������� �������� ������ ---
��� 0: 25
��� 1: 20.48
��� 2: 16.864
��� 3: 13.9712
��� 4: 11.657
��� 5: 9.80557
��� 6: 8.32445
��� 7: 7.13956
��� 8: 6.19165
��� 9: 5.43332
��� 10: 4.82666

--- ���������� ���������� ������ ---
��� 0: 25
��� 1: 21.8982
��� 2: -355.583
��� 3: -570.287
��� 4: -76318
��� 5: -256189
��� 6: -3.49487e+09
��� 7: -4.21755e+10
��� 8: -7.32846e+18
��� 9: -1.07312e+21
��� 10: -3.22238e+37

![������](graphics.png)
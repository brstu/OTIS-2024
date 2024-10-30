#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ��������� ������
const double alpha = 0.95;
const double b = 0.2;
const double c = 1.0;
const double d = 1.5;
const double K = 0.73;
const double T0 = 1.4;
const double TD = 1.0;
const double T = 1.25;
const double w = 34.1;

// ������� ��� ���������� ������������ �������
double calculateControlSignal(double u_prev, const vector<double>& e) {
    double q0 = K * (1 + TD / T0);
    double q1 = -K * (1 + 2 * TD / T0 - T0 / T);
    double q2 = K * (TD / T0);

    return u_prev + q0 * e.back() + q1 * e[e.size() - 2] + q2 * e[e.size() - 3];
}

// ������� ��� ���������� ��������� �������
double calculateOutputSignal(double y_prev, double y_prev_prev, double u) {
    return alpha * y_prev - b * y_prev_prev + c * u + d * sin(u);
}

// �������� ������� �������������
void unlinear_model() {
    const short int y_start = 3;
    double u = 1.0;

    vector<double> y;
    vector<double> u_pred(2, u); // ������������� ������� u_pred � ����� ����������
    vector<double> e = { w - y_start, w - (alpha * y_start + c * u + d * sin(u)) };

    // ��������� ��������
    y.push_back(calculateOutputSignal(y_start, y_start, u));

    // ���� �������������
    while (abs(e.back()) > 0.001) {
        e.push_back(w - y.back()); // ���������� ������
        u = calculateControlSignal(u_pred.back(), e); // ���������� ������������ �������
        y.push_back(calculateOutputSignal(y.back(), y[y.size() - 2], u)); // ���������� ��������� �������
        u_pred.push_back(u); // ���������� ������ ������������ �������
    }

    // ����� ����������� �������������
    cout << "���������� ��������� �����������:\n\n";
    for (size_t i = 0; i < y.size(); i++) {
        cout << "y[" << i << "] = " << y[i] << "; ";
        cout << "e[" << i << "] = " << e[i] << "; ";
        cout << "u[" << i << "] = " << u_pred[i] << "; " << endl;
    }
}

int main() {
    unlinear_model(); // ����� ������� �������������
    return 0;
}
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
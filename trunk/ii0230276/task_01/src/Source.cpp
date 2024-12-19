#include <iostream>
#include <cmath>
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
    double u[10];
    double y0 = 2, y_non = y;
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
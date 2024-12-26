#include <iostream>
#include <math.h>


const double a = 0.52;
const double b = 0.0015;
const double c = 0.32;
const double d = 0.51;

using namespace std;

/*
 * non-linear model
 */
void linear(double u, double y0, int t) {
    cout << "Linear model: " << endl;
    for (int i = 0; i < t; i++) {
        cout << "\ty" << i + 1 << " = " << y0 << endl;
        y0 = a * y0 + b * u;
    }
}

/*
 * non-linear model
 */
void nonLinear(double u, double y0, double y1, int t) {
    cout << "Non-linear model: " << endl;
    for (int i = 0; i < t; i++) {
        cout << "\ty" << i + 1 << " = " << y0 << endl;
        double temp = a * y0 - b * pow(y1, 2) + c * u + d * sin(u);
        y1 = y0;
        y0 = temp;
    }
}

int main() {

    double u, y0;

    cout << "u0 > "; 
    cin >> u;
    cout << "y0 > "; 
    cin >> y0;

    linear(u, y0, 10);
    nonLinear(u, y0, y0 + 0.015, 10);

    return 0;
}
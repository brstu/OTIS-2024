#include<iostream>
#include<cmath>

using namespace std;

double a = 0.8;

double b = 0.4;

double c = 0.6;

double d = 0.7;


double Linear(double u, double y) {
    return a * y + b * u;
}

double NonLinear(double y,double u,double yPrev,double uPrev) {
    return a * y - b * pow(yPrev, 2) + c * u - d * sin(uPrev);
}

int main() {


    double y=15;

    double yNext = y;
    double yPrev;
    double u = 5;
    double uPrev;

    uPrev = u;  

    int steps = 10;

    cout << "Linear Model: " << endl;
    for (int i = 0; i < steps; i++) {
        yPrev = yNext;
        yNext = Linear(yNext, u);
        cout << i + 1 << ":" << yNext << endl;
    }
    cout << endl;

    cout << "NonLinear Model : " << endl;
    for (int i = 0; i< steps; i++) {
        yPrev = yNext;
        yNext = NonLinear(yNext, u,uPrev,yPrev);
        cout << i + 1 << ":" << yNext << endl;
    }


    return 0;

}

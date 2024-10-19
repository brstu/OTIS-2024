#include <iostream>
#include <cmath>
using namespace std;
const double a = 0.3;
const double b = 0.5;
const double c = 0.9;
const double d = 0.2;

void linearModel(double u, double inputY, double y){
    for(int i = 0;i < 10;i++){
        y = a * inputY + b * u;
        inputY = y;
        cout << i + 1 << ": " << y << endl;
    }
}
void nonLinearModel(double u, double inputYForNonLinear, double prevY, double nextY){
    for(int i = 0;i < 10;i++) {
        prevY = inputYForNonLinear;
        nextY = a * inputYForNonLinear - b * pow(prevY, 2) + c * u + d * sin(u - 1);
        inputYForNonLinear = nextY;
        cout << i + 1 << ": " << nextY << endl;
    }
}
int main() {
    double prevY = 0.0;
    double nextY = 0.0;
    double inputYForNonLinear = 1.0;
    double yLinear = 0.0;
    double inputYLinear = 1.0;
    double u = 2.0;
    cout << "Linear model: " << endl;
    linearModel(u, inputYLinear, yLinear);
    cout << endl;
    cout << "Non Linear Model: " << endl;
    nonLinearModel(u, inputYForNonLinear, prevY, nextY);
    return 0;
}
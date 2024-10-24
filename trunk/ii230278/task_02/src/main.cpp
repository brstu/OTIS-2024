#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double A = 0.5,
B = 0.6,
C = 0.6, 
D = 0.6;

double gainn = 0.8,
T_const_0 = 1.1,
T_delay = 1.0,
T_const = 1.1, 
des = 20;

double num_0 = gainn * (1 + (T_delay / T_const_0)),
       num_1 = -gainn * (1 + 2 * (T_delay / T_const_0) - (T_const_0 / T_const)),
       num_2 = gainn * (T_delay / T_const_0);

void nonLinear() {
    const double init_output = 2;
    vector<double> output;
    output.push_back(init_output);
    double controlSign = 1.0; 
    vector<double> err;
    err.push_back(des - init_output); 
    vector<double> prevSign;
    prevSign.push_back(controlSign); 
    
    while (abs(des - output.back()) > 0.01) {
        double current_err = des - output.back();  
        err.push_back(current_err);  
        
        controlSign = prevSign.back() +
                         num_0 * current_err +
                         num_1 * (err.size() > 1 ? err[err.size() - 2] : 0) +
                         num_2 * (err.size() > 2 ? err[err.size() - 3] : 0);
        
        output.push_back(A * output.back() -
                         B * (output.size() > 1 ? output[output.size() - 2] : init_output) +
                         C * controlSign +
                         D * sin(prevSign.back()));

        prevSign.push_back(controlSign);
    }

    cout << "SteptOutputterrtControl Signaln";
    cout << endl;
    int i = 0;
    while(i < output.size())
        cout << i + 1 << " t " << output[i] << " t " << (des - output[i]) << " t " << prevSign[i] << endl;
    ++i;
}

int main() {
    nonLinear();
}

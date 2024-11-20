#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    float alpha = 0.6, beta = 0.8, gamma = 0.2, delta = 1.0;
    float K = 0.9, initial_time = 0.5, ts = 1.0, td = 0.5, output = 10;
    float q0 = K * (1 + (td / initial_time)),
          q1 = -K * (1 + 2 * (td / initial_time) - (initial_time / ts)),
          q2 = K * (td / initial_time);
    
    const short int n = 2;
    vector<float> result = {n, n};
    vector<float> error = {output - n, output - n};
    float control = 1;
    vector<float> ctrl = {control, control};
    
    while (abs(output - result.back()) > 1) {
        error.push_back(output - result.back());
        control = ctrl.back() + q0 * error.back() + q1 * error[error.size() - 2] + q2 * error[error.size() - 3];
        result.push_back(alpha * result.back() - beta * result[result.size() - 2] + gamma * control + delta * sin(ctrl.back()));
        ctrl.push_back(control);
    }
    
    cout << right << setw(10) << "It" << setw(10) << right << "Output" << setw(13) << right << "Error"
         << setw(13) << right << "Control" << endl;
    
    for (int i = 0; i < result.size(); i++) {
        cout << right << setw(10) << i + 1 << setw(10) << result[i] << setw(13) << error[i] << setw(13) << ctrl[i] << endl;
    }
    
    return 0;
}
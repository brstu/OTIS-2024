#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

float a = 0.6, b = 0.8, c = 0.2, d = 1.0, e = 0.2;

vector<float> Linear(int tau, float temp) {
    vector<float> res(tau); res[0] = temp;
    for (int i = 1; i < tau; i++) {
        res[i] = a * res[i - 1] + b * e;
    }
    return res;
}
vector<float> Nonlinear(int tau, float temp) {
    vector<float> res(tau); res[0] = temp;
    if (tau > 1) res[1] = a * res[0] + c * e + d * sin(e); 
    for (int i = 2; i < tau; i++) {
        res[i] = a * res[i - 1] - b * pow(res[i - 2], 2) + c * e + d * sin(e);
    }
    return res;
}
int main() {
    float startTemperature; int tau; vector<vector<float>> results;
    cout << "Enter Start T: "; cin >> startTemperature;
    cout << "Enter Time: "; cin >> tau; tau++;
    results.push_back(Linear(tau, startTemperature));
    results.push_back(Nonlinear(tau, startTemperature));
    cout << right << setw(10)<< "It:" << setw(10) << right << "Linear" << setw(13) << right << "No-Linear" << endl;
    for (int i = 0; i < tau; i++) {
        cout << right << setw(10) << i << setw(10) << results[0][i] << setw(13) << results[1][i] << endl;
    }
    return 0;
}
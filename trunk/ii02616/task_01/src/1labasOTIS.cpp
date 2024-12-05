#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

float alf = 0.6, bet = 0.8, c = 0.2, dlt = 1.0, es = 0.2;

vector<float> Linear(int tau, float temp) {
    vector<float> res(tau); res[0] = temp;
    for (int i = 1; i < tau; i++) {
        res[i] = alf * res[i - 1] + bet * es;
    }
    return res;
}
vector<float> Nonlinear(int tau, float temp) {
    vector<float> res(tau); res[0] = temp;
    if (tau > 1) res[1] = alf * res[0] + c * es + dlt * sin(es);
    for (int i = 2; i < tau; i++) {
        res[i] = alf * res[i - 1] - bet * pow(res[i - 2], 2) + c * es + dlt * sin(es);
    }
    return res;
}
int main() {
    setlocale(LC_ALL, "Russian");
    float startTemperature; int tau; vector<vector<float>> results;
    cout << "Введите начальное T: "; cin >> startTemperature;
    cout << "Введите шаг: "; cin >> tau; tau++;
    results.push_back(Linear(tau, startTemperature));
    results.push_back(Nonlinear(tau, startTemperature));
    cout << right << setw(10) << "It:" << setw(10) << right << "Linear" << setw(13) << right << "No-Linear" << endl;
    for (int i = 0; i < tau; i++) {
        cout << right << setw(10) << i << setw(10) << results[0][i] << setw(13) << results[1][i] << endl;
    }
    return 0;
}
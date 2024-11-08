#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {  
    float а = 0.6, б = 0.8, в = 0.2, г = 1.0;
    float К = 0.9, нач_время = 0.5, тс = 1.0, тд = 0.5, output = 10;
    float q0 = К * (1 + (тд / нач_время)), q1 = -К * (1 + 2 * (тд / нач_время) - (нач_время / тс)), q2 = К * (тд / нач_время);
    const short int n = 2;
    vector<float> результат = {n, n};
    vector<float> ошибка = { output - n, output - n};
    float control = 1;
    vector<float> ctrl = {control,control};
    while (abs(output - результат.back()) > 1) {
        ошибка.push_back(output - результат.back());
        control = ctrl.back() + q0 * ошибка.back() + q1 * ошибка[ошибка.size() - 2] + q2 * ошибка[ошибка.size() - 3];
        результат.push_back(а * результат.back() - б * результат[результат.size()-2] + в * control + г * sin(ctrl.back()));
        ctrl.push_back(control);
    }
    cout << right << setw(10) << "It" << setw(10) << right << "Output" << setw(13) << right << "Error" 
    << setw(13) << right << "Control" << endl;
    for (int i = 0; i < результат.size(); i++) {
        cout << right << setw(10) << i+1 << setw(10) << результат[i] << setw(13) << ошибка[i] << setw(13) << ctrl[i] << endl;
    }
    return 0;
}
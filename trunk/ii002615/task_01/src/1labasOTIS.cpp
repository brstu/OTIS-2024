#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

float альфа = 0.6, бета = 0.8, с = 0.2, дельта = 1.0, еpsilon = 0.2;

vector<float> Линейный(int шаг, float начальнаяТемпература) {
    vector<float> результат(шаг);
    результат[0] = начальнаяТемпература;

    for (int i = 1; i < шаг; ++i) {
        результат[i] = альфа * результат[i - 1] + бета * еpsilon;
    }
    return результат;
}

vector<float> Нелинейный(int шаг, float начальнаяТемпература) {
    vector<float> результат(шаг);
    результат[0] = начальнаяТемпература;

    if (шаг > 1) {
        результат[1] = альфа * результат[0] + с * еpsilon + дельта * sin(epsilon);
    }
    
    for (int i = 2; i < шаг; ++i) {
        результат[i] = альфа * результат[i - 1] - бета * pow(результат[i - 2], 2) + с * еpsilon + дельта * sin(epsilon);
    }
    return результат;
}

int main() {
    setlocale(LC_ALL, "Russian");
    float начальнаяТемпература;
    int шаг;
    vector<vector<float>> результаты;

    cout << "Введите начальное значение T: ";
    cin >> начальнаяТемпература;

    cout << "Введите количество шагов: ";
    cin >> шаг;
    шаг++;

    результаты.push_back(Линейный(шаг, начальнаяТемпература));
    результаты.push_back(Нелинейный(шаг, начальнаяТемпература));

    cout << right << setw(10) << "Ит:" << setw(10) << right << "Линейный" << setw(13) << right << "Нелинейный" << endl;

    for (int i = 0; i < шаг; ++i) {
        cout << right << setw(10) << i << setw(10) << результаты[0][i] << setw(13) << результаты[1][i] << endl;
    }

    return 0;
}
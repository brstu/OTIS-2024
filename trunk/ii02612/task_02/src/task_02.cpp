#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Коэффициенты системы
double const a = 0.9;
double const b = 0.3;
double const c = 0.4;
double const d = 0.1;


// Параметры системы
double trans_coeff_K = 0.9;
double time0 = 0.5, timeC = 1.0, timeD = 0.5;
double req_output = 20;

// Параметры регулятора
double
par1 = trans_coeff_K * (1 + (timeD / time0)),
par2 = -trans_coeff_K * (1 + 2 * (timeD / time0) - (time0 / timeC)),
par3 = trans_coeff_K * (timeD / time0);


void NonlinearMod() {
    //Стартовые значения
    const short int init = 2;
    std::vector<double> nonlinearResult = { init, init }; // Вектор результатовм модели
    std::vector<double> err = { req_output - init, req_output - init }; // Вектор полученных ошибок
    double ctrl_signal = 1;
    std::vector<double> ctrl = { ctrl_signal,ctrl_signal }; // Вектор контрольных сигналов


    while (abs(req_output - nonlinearResult.back()) > 0.01) {
        err.push_back(req_output - nonlinearResult.back()); // Обновление ошибки
        ctrl_signal = ctrl.back() + par1 * err.back() + par2 * err[err.size() - 2] + par3 * err[err.size() - 3];
        nonlinearResult.push_back(a * nonlinearResult.back() - b * nonlinearResult[nonlinearResult.size()-2] + c * ctrl_signal + d * sin(ctrl.back()));
        ctrl.push_back(ctrl_signal);
    }

    std::cout << std::right << std::setw(10) << "Итерация"
        << std::setw(10) << std::right << "Вывод"
        << std::setw(13) << std::right << "Ошибка" 
        << std::setw(13) << std::right << "Контроль" << std::endl;

    for (int i = 0; i < nonlinearResult.size(); i++) {
        std::cout << std::right << std::setw(10) << i+1
            << std::setw(10) << nonlinearResult[i]
            << std::setw(13) << err[i]
            << std::setw(13) << ctrl[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    NonlinearMod();
    return 0;
}
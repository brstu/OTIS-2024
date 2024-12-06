﻿#include <iostream>
#include <vector>
#include <cmath>

class NonlinearSystem {
public:
    NonlinearSystem(double addd, double saaww, double qwer, double asdf, double zxcv, double rtyu, double fghj, double cvbn, double plmn)
        : a(addd), b(saaww), c(qwer), d(asdf), k(zxcv), t0(rtyu), delay(fghj), t(cvbn), desired_output(plmn) {
        r0 = k * (1 + (delay / t0));
        r1 = -k * (1 + 2 * (delay / t0) - (t0 / t));
        r2 = k * (delay / t0);
    }

    void simulate() {
        const short int initial_input = 2;
        std::vector<double> output = { initial_input, initial_input };
        double control_signal = 1.0;
        std::vector<double> error = { desired_output - initial_input, desired_output - initial_input };
        std::vector<double> prev_control_signal = { control_signal };

        while (std::abs(desired_output - output.back()) > 0.01) {
            double current_error = desired_output - output.back();
            error.push_back(current_error);

            control_signal = prev_control_signal.back() + r0 * current_error + r1 * error[error.size() - 2] + r2 * error[error.size() - 3];
            output.push_back(a * output.back() - b * output[output.size() - 2] + c * control_signal + d * std::sin(prev_control_signal.back()));
            prev_control_signal.push_back(control_signal);
        }

        printResults(output, error, prev_control_signal);
    }

private:
    double a, b, c, d;
    double k, t0, delay, t, desired_output;
    double r0, r1, r2;

    void printResults(const std::vector<double>& output, const std::vector<double>& error, const std::vector<double>& prev_control_signal) {
        std::cout << "Step\tOutput\tError\tControl Signal\n";
        for (size_t i = 0; i < output.size(); i++) {
            std::cout << i + 1 << "\t" << output[i] << "\t" << error[i] << "\t" << prev_control_signal[i] << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    double addd, saaww, qwer, asdf, zxcv, rtyu, fghj, cvbn, plmn;

    std::cout << "Введите коэффициенты системы:\n";
    std::cout << "addd: "; std::cin >> addd;
    std::cout << "saaww: "; std::cin >> saaww;
    std::cout << "qwer: "; std::cin >> qwer;
    std::cout << "asdf: "; std::cin >> asdf;

    std::cout << "Введите параметры системы:\n";
    std::cout << "zxcv: "; std::cin >> zxcv;
    std::cout << "rtyu: "; std::cin >> rtyu;
    std::cout << "fghj: "; std::cin >> fghj;
    std::cout << "cvbn: "; std::cin >> cvbn;
    std::cout << "plmn (желаемое значение выхода): "; std::cin >> plmn;

    NonlinearSystem system(addd, saaww, qwer, asdf, zxcv, rtyu, fghj, cvbn, plmn);
    system.simulate();

    return 0;
}
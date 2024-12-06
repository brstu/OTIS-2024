#include <iostream>
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
        double output = initial_input;
        double control_signal = 1.0;
        double error1 = desired_output - initial_input;
        double error2 = error1;

        std::cout << "Step\tOutput\tError\tControl Signal\n";
        std::cout << 1 << "\t" << output << "\t" << error1 << "\t" << control_signal << std::endl;

        int step = 2;
        while (std::abs(desired_output - output) > 0.01) {
            double current_error = desired_output - output;

            control_signal = control_signal + r0 * current_error + r1 * error1 + r2 * error2;
            output = a * output - b * initial_input + c * control_signal + d * std::sin(control_signal);

            error2 = error1;
            error1 = current_error;

            std::cout << step << "\t" << output << "\t" << current_error << "\t" << control_signal << std::endl;
            step++;
        }
    }

private:
    double a, b, c, d;
    double k, t0, delay, t, desired_output;
    double r0, r1, r2;
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
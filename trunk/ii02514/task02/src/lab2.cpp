#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double A = 0.5;
const double B = 0.6;
const double C = 0.6;
const double D = 0.6;
const double M = 0.8;
const double RO = 1.1;
const double RD = 1.0;
const double R = 1.1;
const double TARGET_VALUE = 20.0;

// ��������������� ������������
const double q0 = M * (1 + (RD / R0));
const double q1 = -M * (1 + 2 * (RD / R0) - (R0 / R));
const double q2 = M * (RD / R0);

void simulateNonlinearModel() {
    const double initialY = 2.0;
    std::vector<double> outputs = { initialY, initialY }; // ������ ��� �������� �������� ���������� y
    double controlSignal = 1.0; // ��������� �������� ����������� ���������� u
    std::vector<double> errors = { TARGET_VALUE - initialY, TARGET_VALUE - initialY }; // ������ ��� �������� �������� �������� TARGET_VALUE - y
    std::vector<double> controlSignals = { controlSignal, controlSignal }; // ������ ��� �������� �������� ���������� ����������� ���������� u

    // �������������
    while (std::abs(TARGET_VALUE - outputs.back()) > 0.01) { // ���� �����������, ���� ������� ����� TARGET_VALUE � ��������� ��������� y ������ 0.01
        errors.push_back(TARGET_VALUE - outputs.back()); // ���������� ������� �������� � ������ errors
        controlSignal = controlSignals.back() + q0 * errors.back() + q1 * errors[errors.size() - 2];

        // �������� �� ������� ������������ ���������� ��������� � errors ��� ������������� q2
        if (errors.size() >= 3) {
            controlSignal += q2 * errors[errors.size() - 3];
        }

        // ���������� ������ �������� ���������� y
        outputs.push_back(A * outputs.back() - B * outputs[outputs.size() - 2] + C * controlSignal + D * std::sin(controlSignals.back()));
        controlSignals.push_back(controlSignal); // ���������� ������ �������� ����������� ���������� u � ������ controlSignals
    }

    // ����� ����������� �������������
    for (std::size_t i = 0; i < outputs.size(); i++) {
        std::cout << i + 1 << ") y[" << i << "] = " << outputs[i] << std::setw(15);
        std::cout << "e[" << i << "] = " << errors[i] << std::setw(15);
        std::cout << "u_pr[" << i << "] = " << controlSignals[i] << std::endl; // ����� �������� y, e � u_pr �� ������ �������� �����
    }
}

int main() {
    simulateNonlinearModel(); // ����� ������� �������������
    return 0;
}
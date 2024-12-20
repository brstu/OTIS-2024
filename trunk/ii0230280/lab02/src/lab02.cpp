#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class NonlinearSystem {
private:
    double coeff_K = 0.0001;
    double time_const = 100.0;
    double delay_time = 100.0;
    double init_time = 1.0;

    double calc_q0 = coeff_K * (1 + delay_time / init_time);
    double calc_q1 = -coeff_K * (1 + 2 * delay_time / init_time - init_time / time_const);
    double calc_q2 = coeff_K * delay_time / init_time;

    vector<double> coeffs = { calc_q0, calc_q1, calc_q2 };
    vector<double> errors = { 0, 0, 0 };
    vector<double> output_vals = { 0, 0, 0 };
    vector<double> control_vals = { 1, 1 };

    double calculateSum() {
        double result = 0.0;
        for (size_t i = 0; i < coeffs.size(); i++) {
            result += coeffs[i] * errors[i];
        }
        return result;
    }

public:
    void simulateSystem(int duration, double targetValue, double paramA = 0.5, double paramB = 0.3,
        double paramC = 0.9, double paramD = 0.7) {
        for (int step = 0; step < duration; ++step) {

            errors[0] = targetValue - output_vals[output_vals.size() - 1];
            errors[1] = targetValue - output_vals[output_vals.size() - 2];
            errors[2] = targetValue - output_vals[output_vals.size() - 3];

            control_vals[0] = control_vals[1] + calculateSum();

            double newOutput = paramA * output_vals[output_vals.size() - 1]
                - paramB * pow(output_vals[output_vals.size() - 2], 2)
                + paramC * control_vals[0]
                + paramD * sin(control_vals[1]);

            output_vals.push_back(newOutput);
            control_vals[1] = control_vals[0];
        }
    }

    const vector<double>& getOutputValues() const {
        return output_vals;
    }
};

int main() {
    double desiredValue;
    ofstream outputFile("simulation_output.txt");
    NonlinearSystem system;

    if (outputFile.is_open()) {
        cout << "Enter the target value (setpoint): ";
        cin >> desiredValue;

        system.simulateSystem(100, desiredValue);

        const vector<double>& results = system.getOutputValues();

        for (size_t index = 0; index < results.size(); ++index) {
            double scaledResult = results[index] * desiredValue / results[results.size() - 1];
            cout << index << " " << scaledResult << endl;
            outputFile << index << " " << scaledResult << endl;
        }

        outputFile.close();
    }
    else {
        cerr << "Error: Failed to open output file." << endl;
    }

    return 0;
}

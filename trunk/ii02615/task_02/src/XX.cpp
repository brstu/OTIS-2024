#include <iostream>
#include <vector>

using namespace std;

// ПАРАМЕТРЫ РЕГУЛЯТОРА, СИСТЕМЫ И КОЭФИЦЕНТЫ СИСТЕМЫ
double a = 0.5, b = 0.6, c = 0.6, d = 0.6;
double IN = 0.8, a0 = 1.1, adelay = 1.0, aconst = 1.1, AAA_output = 20;

double reg0 = IN * (1 + (adelay / a0)),
reg1 = -IN * (1 + 2 * (adelay / a0) - (a0 / aconst)),
reg2 = IN * (adelay / a0);

void NON();

int main() {
	NON();
}
void NON() {
	
	const short int initial_output = 2;
	vector<double> output = { initial_output, initial_output };  
	double control_signal = 1.0;  
	vector<double> error = { AAA_output - initial_output, AAA_output - initial_output };  
	vector<double> previous_control_signal = { control_signal, control_signal };  

	
	while (abs(AAA_output - output.back()) > 0.01)
	{
		error.push_back(AAA_output - output.back());  
		control_signal = previous_control_signal.back() + reg0 * error.back() + reg1 * error[error.size() - 2] + reg2 * error[error.size() - 3];
		
		output.push_back(a * output.back() - b * output[output.size() - 2] + c * control_signal + d * sin(previous_control_signal.back()));
		previous_control_signal.push_back(control_signal);  
	}

	
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < output.size(); i++)
		cout << i + 1 << ";" << output[i] << ";" << error[i] << ";" << previous_control_signal[i] << endl;
}
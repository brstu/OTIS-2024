﻿#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


double systemCoeffA = 0.5, systemCoeffB = 0.6, systemCoeffC = 0.6, systemCoeffD = 0.6;

double systemGain = 0.8, timeConstant0 = 1.1, systemDelay = 1.0, timeConstant = 1.1, targetOutput = 20;

double controllerParam0 = systemGain * (1 + (systemDelay / timeConstant0)),
controllerParam1 = -systemGain * (1 + 2 * (systemDelay / timeConstant0) - (timeConstant0 / timeConstant)),
controllerParam2 = systemGain * (systemDelay / timeConstant0);

void runNonlinearSystem() {
	
	const short int initialOutput = 2;
	vector<double> outputValues = { initialOutput, initialOutput };  
	double controlInput = 1.0;  
	vector<double> errorValues = { targetOutput - initialOutput, targetOutput - initialOutput }; 
	vector<double> previousControlInputs = { controlInput, controlInput };  

	
	while (abs(targetOutput - outputValues.back()) > 0.01)
	{
		errorValues.push_back(targetOutput - outputValues.back());  
		controlInput = previousControlInputs.back() + controllerParam0 * errorValues.back() + controllerParam1 * errorValues[errorValues.size() - 2] + controllerParam2 * errorValues[errorValues.size() - 3];
		
		outputValues.push_back(systemCoeffA * outputValues.back() - systemCoeffB * outputValues[outputValues.size() - 2] + systemCoeffC * controlInput + systemCoeffD * sin(previousControlInputs.back()));
		previousControlInputs.push_back(controlInput);  
	}

	
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < outputValues.size(); i++)
		cout << i + 1 << ";" << outputValues[i] << ";" << errorValues[i] << ";" << previousControlInputs[i] << endl;
}

int main() {
	runNonlinearSystem();
}
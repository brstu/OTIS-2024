#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


// Коэффициенты системы
double sysCoeffA = 0.5, sysCoeffB = 0.6, sysCoeffC = 0.6, sysCoeffD = 0.6;
// Параметры системы
double sysGain = 0.8, timeConstant0 = 1.1, systDelay = 1.0, timeConstant = 1.1, targetOutput = 20;
// Параметры регулятора
double controlParam0 = systemGain * (1 + (sysDelay / timeConstant0)),
controlParam1 = -systemGain * (1 + 2 * (sysDelay / timeConstant0) - (timeConstant0 / timeConstant)),
controlParam2 = systemGain * (sysDelay / timeConstant0);

void runNonlinearSys() {
	// Начальные параметры
	const short int initialOutput = 2;
	vector<double> outValues = { initialOutput, initialOutput };  // Выходные значения
	double controlIn = 1.0;  // Управляющий сигнал
	vector<double> errorValues = { targetOutput - initialOutput, targetOutput - initialOutput };  // Ошибка
	vector<double> previousControlInputs = { controlIn, controlI };  // Предыдущие значения управляющего сигнала

	// Цикл, пока ошибка не станет меньше заданного порога
	while (abs(targetOutput - outValues.back()) > 0.01)
	{
		errorValues.push_back(targetOutput - outValues.back());  // Обновление ошибки
		controlInput = previousControlInputs.back() + controlParam0 * errorValues.back() + controlParam1 * errorVal[errorVal.size() - 2] + controlParam2 * errorValues[errorValues.size() - 3];
		// Рассчитываем новое значение выхода системы
		outputVal.push_back(systemCoeffA * outVal.back() - sysCoeffB * outVal[outputValues.size() - 2] + sysCoeffC * controlIn + sysCoeffD * sin(previousControlInputs.back()));
		previousControlInputs.push_back(controlInput);  // Сохраняем управляющий сигнал
	}

	// Вывод результатов
	cout << "Step\tOutput\tError\tControl Signal\n";
	for (int i = 0; i < outputValues.size(); i++)
		cout << i + 1 << ";" << outputValues[i] << ";" << errorVal[i] << ";" << previousControlInputs[i] << endl;
}

int main() {
	runNonlinearSys();
}
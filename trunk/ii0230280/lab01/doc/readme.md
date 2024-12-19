Чем занимается этот проект
Данный код контролирует температуру некоторого объекта , которая описана дифферинциальными уравненинями .

Какая польза от этого проекта
Этот код полезен тем , что он , благодрая входной температуре, может моделировать температуру данного объекта.

Функции данного кода
double CalculateLinear(double input, double output) {
    return coeffA * output + coeffB * input;
}

double CalculateNonLinear(double currentOutput, double currentInput, double previousOutput, double previousInput) {
    return coeffA * currentOutput - coeffB * pow(previousOutput, 2) + coeffC * currentInput - coeffD * sin(previousInput);
}

Куда можно будет обратиться
Если будут возникать какие-то вопросы по этому проекту, вы можете зайти в мой профиль в GitHub и перейти в социальные сети, где в дальнейшем сможете задать ваши вопросы.
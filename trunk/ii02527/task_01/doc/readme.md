Лабораторная 01
Цель работы: Создание линейной и нелинейной модели для симуляции температуры объекта.

Код программы:
```
double u(unsigned int t) {
	return a0 * t + u0;
}


double linearModel(unsigned int t) {
	if (t < 1)
		return y00;

	return a * linearModel(t - 1) + b * u(t - 1);
}

double nonlinearModel(unsigned int t) {
	if (t < 1)
		return y00;

	if (t < 2)
		return y01;

	return a * nonlinearModel(t - 1) - b * pow(nonlinearModel(t - 2), 2) + c * u(t - 1) + d * sin(u(t - 2));
}```

Вывод: В ходе лабораторной работы создал линейную и нелинейную модель для симуляции температуры объекта.
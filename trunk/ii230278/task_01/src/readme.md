# Лабораторная работа 1

В ходе лабораторной работы реализовал линейную и нелинейную модели для отслеживания температуры

```C++
void linearModel(double u, double inputY, double y){
for(int i = 0;i < 10;i++){
y = a * inputY + b * u;
inputY = y;
cout << i + 1 << ": " << y << endl;
}
}
void nonLinearModel(double u, double inputYForNonLinear, double prevY, double nextY){
for(int i = 0;i < 10;i++) {
prevY = inputYForNonLinear;
nextY = a * inputYForNonLinear - b * pow(prevY, 2) + c * u + d * sin(u - 1);
inputYForNonLinear = nextY;
cout << i + 1 << ": " << nextY << endl;
}
}
```

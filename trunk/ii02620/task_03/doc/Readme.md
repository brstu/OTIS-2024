<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Применение знаний алгоритмов для графов на практике”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Хитренко А. А.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc (где xx - номер группы, yy - номер студента, например ii02302)..
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
## Задание ##
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

<hr>

# Выполнение задания #

Код программы:

```cpp
 #include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

class Vertex {
public:
    string title;
    string data;
    string link;

    Vertex() = default;
    Vertex(const string& vertexTitle) : title(vertexTitle) {}
};

class Connection {
public:
    string start;
    string end;
    bool isDirected;

    Connection(const string& start, const string& end, bool directed = false)
        : start(start), end(end), isDirected(directed) {}
};

class Network {
public:
    string title;
    bool isDirected;
    unordered_map<string, Vertex> vertices;
    vector<Connection> connections;

    Network(const string& networkTitle, bool directed)
        : title(networkTitle), isDirected(directed) {}

    void addVertex(const string& vertexTitle) {
        if (vertices.find(vertexTitle) == vertices.end()) {
            vertices[vertexTitle] = Vertex(vertexTitle);
            cout << "Узел " << vertexTitle << " добавлен." << endl;
        }
        else {
            cout << "Узел " << vertexTitle << " уже существует." << endl;
        }
    }

    void removeVertex(const string& vertexTitle) {
        if (vertices.erase(vertexTitle)) {
            connections.erase(remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
                return connection.start == vertexTitle || connection.end == vertexTitle;
                }), connections.end());
            cout << "Узел " << vertexTitle << " удалён." << endl;
        }
        else {
            cout << "Узел " << vertexTitle << " не существует." << endl;
        }
    }

    void addConnection(const string& start, const string& end) {
        if (vertices.find(start) != vertices.end() && vertices.find(end) != vertices.end()) {
            connections.emplace_back(start, end, isDirected);
            cout << "Ребро от " << start << " до " << end << " добавлено." << endl;
        }
        else {
            cout << "Одно или оба узла не существует." << endl;
        }
    }

    void removeConnection(const string& start, const string& end) {
        connections.erase(remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
            return connection.start == start && connection.end == end;
            }), connections.end());
        cout << "Ребро от " << start << " до " << end << " удалено." << endl;
    }

    void exportNetwork(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << title << " : " << (isDirected ? "ориентированный" : "неориентированный") << " ;" << endl;
            for (const auto& vertexPair : vertices) {
                outFile << vertexPair.first << " ";
            }
            outFile << ";" << endl;
            for (const auto& connection : connections) {
                outFile << connection.start << " -> " << connection.end << " ;" << endl;
            }
            outFile.close();
            cout << "Граф экспортирован в " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для экспорта." << endl;
        }
    }

    void importNetwork(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            vertices.clear();
            connections.clear();
            string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            title = line.substr(0, pos);
            isDirected = line.find("ориентированный") != string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                string vertexTitle = line.substr(0, pos);
                addVertex(vertexTitle);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addVertex(line);

            while (getline(inFile, line)) {
                pos = line.find(" -> ");
                if (pos != string::npos) {
                    string start = line.substr(0, pos);
                    line.erase(0, pos + 4);
                    pos = line.find(" ;");
                    string end = line.substr(0, pos);
                    addConnection(start, end);
                }
            }
            inFile.close();
            cout << "Граф импортирован из " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для импорта." << endl;
        }
    }

    void displayInfo() {
        cout << "Граф: " << title << endl;
        cout << "Количество узлов: " << vertices.size() << endl;
        cout << "Количество рёбер: " << connections.size() << endl;
    }

    void drawNetwork() {
        cout << endl << "--- Представление графиков в формате ASCII ---" << endl;
        for (const auto& connection : connections) {
            cout << setw(2) << connection.start << " --> " << connection.end << endl;
            if (!isDirected) {
                cout << setw(2) << connection.end << " --> " << connection.start << endl;
            }
        }
        cout << "----------------------------------" << endl;
    }
};

void displayMenu() {
    cout << endl << "--- Меню редактора графа ---" << endl;
    cout << "1. Добавить узел" << endl;
    cout << "2. Удалить узел" << endl;
    cout << "3. Добавить ребро" << endl;
    cout << "4. Удалить ребро" << endl;
    cout << "5. Отобразить информацию о графе" << endl;
    cout << "6. Экспорт графа" << endl;
    cout << "7. Импорт графа" << endl;
    cout << "8. Нарисовать граф" << endl;
    cout << "9. Выйти" << endl;
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    Network network("ExampleNetwork", true);
    int choice;
    string vertexTitle, startVertex, endVertex, filename;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Введите имя узла: ";
            getline(cin, vertexTitle);
            network.addVertex(vertexTitle);
            break;
        case 2:
            cout << "Введите имя узла для удаления: ";
            getline(cin, vertexTitle);
            network.removeVertex(vertexTitle);
            break;
        case 3:
            cout << "Введите узел 'от': ";
            getline(cin, startVertex);
            cout << "Введите узел 'до': ";
            getline(cin, endVertex);
            network.addConnection(startVertex, endVertex);
            break;
        case 4:
            cout << "Введите узел 'от' для удаления: ";
            getline(cin, startVertex);
            cout << "Введите узел 'до' для удаления: ";
            getline(cin, endVertex);
            network.removeConnection(startVertex, endVertex);
            break;
        case 5:
            network.displayInfo();
            break;
        case 6:
            cout << "Введите имя файла для экспорта: ";
            getline(cin, filename);
            network.exportNetwork(filename);
            break;
        case 7:
            cout << "Введите имя файла для импорта: ";
            getline(cin, filename);
            network.importNetwork(filename);
            break;
        case 8:
            network.drawNetwork();
            break;
        case 9:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }

    return 0;
}
```

Результат программы:

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 1
Узел 1 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 2
Узел 2 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 3
Узел 3 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 4
Узел 4 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 5
Узел 5 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 1
Введите имя узла: 6
Узел 6 добавлен.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 3
Введите узел 'от': 1
Введите узел 'до': 2
Ребро от 1 до 2 добавлено.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 3
Введите узел 'от': 1
Введите узел 'до': 3
Ребро от 1 до 3 добавлено.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 3
Введите узел 'от': 4
Введите узел 'до': 6
Ребро от 4 до 6 добавлено.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 3
Введите узел 'от': 1
Введите узел 'до': 4
Ребро от 1 до 4 добавлено.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 5
Граф: ExampleGraph
Количество узлов: 6
Количество рёбер: 4

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 2
Введите имя узла для удаления: 5
Узел 5 удалён.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 4
Введите узел 'от' для удаления: 1
Введите узел 'до' для удаления: 4
Ребро от 1 до 4 удалено.

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 8

--- Представление графиков в формате ASCII ---
 1 --> 2
 1 --> 3
 4 --> 6
----------------------------------

--- Меню редактора графа ---
1. Добавить узел
2. Удалить узел
3. Добавить ребро
4. Удалить ребро
5. Отобразить информацию о графе
6. Экспорт графа
7. Импорт графа
8. Нарисовать граф
9. Выйти
Выберите пункт: 9
Выход из программы.
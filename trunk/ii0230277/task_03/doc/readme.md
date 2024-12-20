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
<p align="right">Группы ИИ-25</p>
<p align="right">Бекназарова А. С.</p>
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

class Node {
public:
    string name;
    string content;
    string fileLink;

    Node() = default;
    Node(const string& nodeName) : name(nodeName) {}
};

class Edge {
public:
    string from;
    string to;
    bool directed;

    Edge(const string& from, const string& to, bool directed = false)
        : from(from), to(to), directed(directed) {}
};

class Graph {
public:
    string name;
    bool isDirected;
    unordered_map<string, Node> nodes;
    vector<Edge> edges;

    Graph(const string& graphName, bool directed)
        : name(graphName), isDirected(directed) {}

    void addNode(const string& nodeName) {
        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node(nodeName);
            cout << "Узел " << nodeName << " добавлен." << endl;
        }
        else {
            cout << "Узел " << nodeName << " уже существует." << endl;
        }
    }

    void removeNode(const string& nodeName) {
        if (nodes.erase(nodeName)) {
            edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
                return edge.from == nodeName || edge.to == nodeName;
                }), edges.end());
            cout << "Узел " << nodeName << " удалён." << endl;
        }
        else {
            cout << "Узел " << nodeName << " не существует." << endl;
        }
    }

    void addEdge(const string& from, const string& to) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            edges.emplace_back(from, to, isDirected);
            cout << "Ребро от " << from << " до " << to << " добавлено." << endl;
        }
        else {
            cout << "Одно или оба узла не существует." << endl;
        }
    }

    void removeEdge(const string& from, const string& to) {
        edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
            return edge.from == from && edge.to == to;
            }), edges.end());
        cout << "Ребро от " << from << " до " << to << " удалено." << endl;
    }

    void exportGraph(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << " : " << (isDirected ? "ориентированный" : "неориентированный") << " ;" << endl;
            for (const auto& nodePair : nodes) {
                outFile << nodePair.first << " ";
            }
            outFile << ";" << endl;
            for (const auto& edge : edges) {
                outFile << edge.from << " -> " << edge.to << " ;" << endl;
            }
            outFile.close();
            cout << "Граф экспортирован в " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для экспорта." << endl;
        }
    }

    void importGraph(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            nodes.clear();
            edges.clear();
            string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            name = line.substr(0, pos);
            isDirected = line.find("ориентированный") != string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                string nodeName = line.substr(0, pos);
                addNode(nodeName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addNode(line);

            while (getline(inFile, line)) {
                pos = line.find(" -> ");
                if (pos != string::npos) {
                    string from = line.substr(0, pos);
                    line.erase(0, pos + 4);
                    pos = line.find(" ;");
                    string to = line.substr(0, pos);
                    addEdge(from, to);
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
        cout << "Граф: " << name << endl;
        cout << "Количество узлов: " << nodes.size() << endl;
        cout << "Количество рёбер: " << edges.size() << endl;
    }

    void drawGraph() {
        cout << endl << "--- Представление графиков в формате ASCII ---" << endl;
        for (const auto& edge : edges) {
            cout << setw(2) << edge.from << " --> " << edge.to << endl;
            if (!isDirected) {
                cout << setw(2) << edge.to << " --> " << edge.from << endl;
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
    Graph graph("ExampleGraph", true);
    int choice;
    string nodeName, fromNode, toNode, filename;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Введите имя узла: ";
            getline(cin, nodeName);
            graph.addNode(nodeName);
            break;
        case 2:
            cout << "Введите имя узла для удаления: ";
            getline(cin, nodeName);
            graph.removeNode(nodeName);
            break;
        case 3:
            cout << "Введите узел 'от': ";
            getline(cin, fromNode);
            cout << "Введите узел 'до': ";
            getline(cin, toNode);
            graph.addEdge(fromNode, toNode);
            break;
        case 4:
            cout << "Введите узел 'от' для удаления: ";
            getline(cin, fromNode);
            cout << "Введите узел 'до' для удаления: ";
            getline(cin, toNode);
            graph.removeEdge(fromNode, toNode);
            break;
        case 5:
            graph.displayInfo();
            break;
        case 6:
            cout << "Введите имя файла для экспорта: ";
            getline(cin, filename);
            graph.exportGraph(filename);
            break;
        case 7:
            cout << "Введите имя файла для импорта: ";
            getline(cin, filename);
            graph.importGraph(filename);
            break;
        case 8:
            graph.drawGraph();
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
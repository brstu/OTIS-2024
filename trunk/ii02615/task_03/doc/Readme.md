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
<p align="right">Рулько М.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_02\doc (где xx - номер группы, yy - номер студента, например ii02302)..
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Задание ##
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

<hr>

# Выполнение задания #

Код программы:
```
#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph {  
private:
    struct Node {  
        int id;
        list<int> neighbors;
    };

    vector<Node> nodes;

public:
    void addNode(int id);
    void addEdge(int from, int to);
    void display() const;
    vector<int> findEulerianCycle();
    vector<int> findHamiltonianCycle();
    Graph createSpanningTree() const;

    bool isEulerian() const;
    bool searchHamiltonian(int u, int v, vector<int>& path, vector<bool>& visited);
};

void Graph::addNode(int id) {
    nodes.push_back({ id, {} });
}

void Graph::addEdge(int from, int to) {
    nodes[from].neighbors.push_back(to);
    nodes[to].neighbors.push_back(from);
}

void Graph::display() const {
    for (const auto& node : nodes) {
        cout << "Node " << node.id << ": ";
        for (int neighbor : node.neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

vector<int> Graph::findEulerianCycle() {
    vector<int> cycle;
    if (!isEulerian()) return cycle;

    vector<bool> visited(nodes.size(), false);
    list<int> stack;
    stack.push_back(0);

    while (!stack.empty()) {
        int current = stack.back();
        if (!nodes[current].neighbors.empty()) {
            int next = nodes[current].neighbors.front();
            stack.push_back(next);
            nodes[current].neighbors.remove(next);
            nodes[next].neighbors.remove(current);
        } else {
            cycle.push_back(current);
            stack.pop_back();
        }
    }
    return cycle;
}

vector<int> Graph::findHamiltonianCycle() {
    vector<int> path(nodes.size(), -1);
    vector<bool> visited(nodes.size(), false);
    visited[0] = true;
    path[0] = 0;

    if (searchHamiltonian(0, 1, path, visited)) {
        return path;
    }
    return {};
}

Graph Graph::createSpanningTree() const {
    Graph tree;
    for (int i = 0; i < nodes.size(); ++i) {
        tree.addNode(i);
    }

    vector<bool> visited(nodes.size(), false);
    visited[0] = true;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : nodes[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                tree.addEdge(current, neighbor);
                q.push(neighbor);
            }
        }
    }
    return tree;
}

bool Graph::isEulerian() const {
    for (const auto& node : nodes) {
        if (node.neighbors.size() % 2 != 0) {
            return false;
        }
    }
    return true;
}

bool Graph::searchHamiltonian(int u, int v, vector<int>& path, vector<bool>& visited) {
    if (v == nodes.size()) {
        return path.front() == path.back();
    }

    for (int neighbor : nodes[u].neighbors) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            path[v] = neighbor;
            if (searchHamiltonian(neighbor, v + 1, path, visited)) {
                return true;
            }
            visited[neighbor] = false;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    Graph graph;  // Изменено название объекта класса

    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    cout << "Структура графа:\n";
    graph.display();

    vector<int> eulerCycle = graph.findEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Эйлеров цикл не найден.\n";
    }

    vector<int> hamiltonianCycle = graph.findHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Гамильтонов цикл не найден.\n";
    }

    Graph spanningTree = graph.createSpanningTree();  // Изменено название объекта класса
    cout << "Создание структуры дерева:\n";
    spanningTree.display();

    return 0;
}




```     
```

Структура графа:
Node 0: 1 4
Node 1: 0 2
Node 2: 1 3
Node 3: 2 4
Node 4: 3 0
Эйлеров цикл: 0 4 3 2 1 0
Гамильтонов цикл не найден.
Создание структуры дерева:
Node 0:
Node 1:
Node 2:
Node 3:
Node 4:
```
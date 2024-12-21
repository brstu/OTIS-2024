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
<p align="right">Андреюк М. О.</p>
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
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
    vector<vector<int>> adjList;

public:
    Graph(int size) : adjList(size) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() const {
        for (int i = 0; i < adjList.size(); ++i) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    bool hasEulerianCycle() const {
        for (const auto& neighbors : adjList) {
            if (neighbors.size() % 2 != 0) return false;
        }
        return true;
    }

    vector<int> findEulerianCycle() const {
        if (!hasEulerianCycle()) return {};
        vector<vector<int>> tempAdj = adjList;
        vector<int> cycle, stack = { 0 };

        while (!stack.empty()) {
            int v = stack.back();
            if (!tempAdj[v].empty()) {
                int u = tempAdj[v].back();
                tempAdj[v].pop_back();
                tempAdj[u].erase(find(tempAdj[u].begin(), tempAdj[u].end(), v));
                stack.push_back(u);
            }
            else {
                cycle.push_back(v);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> findHamiltonianCycle() const {
        vector<int> path = { 0 };
        vector<bool> visited(adjList.size(), false);
        visited[0] = true;

        if (hamiltonianDFS(0, path, visited)) return path;
        return {};
    }

    Graph buildSpanningTree() const {
        Graph tree(adjList.size());
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(curr, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool hamiltonianDFS(int node, vector<int>& path, vector<bool>& visited) const {
        if (path.size() == adjList.size()) {
            return find(adjList[node].begin(), adjList[node].end(), path[0]) != adjList[node].end();
        }

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                if (hamiltonianDFS(neighbor, path, visited)) return true;
                path.pop_back();
                visited[neighbor] = false;
            }
        }
        return false;
    }
};

void initializeGraph(Graph& graph) {
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);
}

void findAndPrintEulerianCycle(const Graph& graph) {
    auto eulerCycle = graph.findEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Eulerian Cycle: ";
        for (int node : eulerCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Eulerian Cycle found." << endl;
    }
}

void findAndPrintHamiltonianCycle(const Graph& graph) {
    auto hamiltonCycle = graph.findHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (int node : hamiltonCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Hamiltonian Cycle found." << endl;
    }
}

void buildAndPrintSpanningTree(const Graph& graph) {
    auto spanningTree = graph.buildSpanningTree();
    cout << "Spanning Tree:" << endl;
    spanningTree.printGraph();
}

int main() {
    Graph graph(5);

    initializeGraph(graph);

    graph.printGraph();

    findAndPrintEulerianCycle(graph);

    findAndPrintHamiltonianCycle(graph);

    buildAndPrintSpanningTree(graph);

    return 0;
}

```

Результат программы:

Node 0: 1 4
Node 1: 0 2
Node 2: 1 3
Node 3: 2 4
Node 4: 3 0
Eulerian Cycle: 0 1 2 3 4 0
Hamiltonian Cycle: 0 1 2 3 4
Spanning Tree:
Node 0: 1 4
Node 1: 0 2
Node 2: 1
Node 3: 4
Node 4: 0 3
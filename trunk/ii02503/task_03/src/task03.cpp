#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
    vector<vector<int>> adjList; // Список смежности

public:
    // Конструктор графа
    Graph(int size) : adjList(size) {}

    // Добавление ребра в граф
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Печать графа
    void printGraph() const {
        for (int i = 0; i < adjList.size(); ++i) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Проверка на наличие эйлерова цикла
    bool hasEulerianCycle() const {
        for (const auto& neighbors : adjList) {
            if (neighbors.size() % 2 != 0) return false;
        }
        return true;
    }

    // Поиск эйлерова цикла
    vector<int> findEulerianCycle() const {
        if (!hasEulerianCycle()) return {};

        vector<vector<int>> tempAdj = adjList; // Временный список смежности
        vector<int> cycle; // Вектор для хранения цикла
        vector<int> stack = { 0 }; // Стек для обхода

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

    // Поиск гамильтонова цикла
    vector<int> findHamiltonianCycle() const {
        vector<int> path = { 0 }; // Начинаем с первой вершины
        vector<bool> visited(adjList.size(), false);
        visited[0] = true;

        if (hamiltonianDFS(0, path, visited)) return path;
        return {};
    }

    // Построение остовного дерева с использованием BFS
    Graph buildSpanningTree() const {
        Graph tree(adjList.size());
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        visited[0] = true; // Начинаем с первой вершины
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
    // Рекурсивная функция для поиска гамильтонова цикла
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

// Инициализация графа с рёбрами
void initializeGraph(Graph& graph) {
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);
}

// Поиск и вывод эйлерова цикла
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

// Поиск и вывод гамильтонова цикла
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

// Построение и вывод остовного дерева
void buildAndPrintSpanningTree(const Graph& graph) {
    auto spanningTree = graph.buildSpanningTree();
    cout << "Spanning Tree:" << endl;
    spanningTree.printGraph();
}

// Главная функция
int main() {
    Graph graph(5); // Создание графа из 5 вершин

    initializeGraph(graph); // Инициализация графа

    cout << "Graph:" << endl;
    graph.printGraph(); // Печать графа

    findAndPrintEulerianCycle(graph); // Поиск и печать эйлерова цикла

    findAndPrintHamiltonianCycle(graph); // Поиск и печать гамильтонова цикла

    buildAndPrintSpanningTree(graph); // Построение и печать остовного дерева

    return 0;
}

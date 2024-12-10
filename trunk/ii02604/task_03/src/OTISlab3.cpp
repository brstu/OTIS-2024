#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph {
private:
    struct Vertex {
        int id;
        list<int> neighbors;
    };

    vector<Vertex> vertices;

    bool isEulerian() const {
        for (const auto& vertex : vertices) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonian(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == vertices.size()) {
            return path.front() == path.back(); // Check if it forms a cycle
        }

        for (int neighbor : vertices[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;
                if (findHamiltonian(neighbor, depth + 1, path, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    void addVertex(int id) {
        vertices.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        vertices[start].neighbors.push_back(end);
        vertices[end].neighbors.push_back(start);
    }

    void printGraph() const {
        cout << "Граф:\n";
        for (const auto& vertex : vertices) {
            cout << "Вершина " << vertex.id << " соединена с: ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    vector<int> getEulerCycle() {
        vector<int> cycle;
        if (!isEulerian()) return cycle;

        vector<bool> visited(vertices.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!vertices[current].neighbors.empty()) {
                int next = vertices[current].neighbors.front();
                stack.push_back(next);
                vertices[current].neighbors.remove(next);
                vertices[next].neighbors.remove(current);
            }
            else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(vertices.size(), -1);
        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        cycle[0] = 0;

        if (findHamiltonian(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph createSpanningTree() const {
        Graph tree;
        for (int i = 0; i < vertices.size(); ++i) {
            tree.addVertex(i);
        }

        vector<bool> visited(vertices.size(), false);
        queue<int> bfsQueue;
        visited[0] = true;
        bfsQueue.push(0);

        while (!bfsQueue.empty()) {
            int current = bfsQueue.front();
            bfsQueue.pop();

            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(current, neighbor);
                    bfsQueue.push(neighbor);
                }
            }
        }
        return tree;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graph g;

    // Добавляем вершины
    for (int i = 0; i < 5; ++i) {
        g.addVertex(i);
    }

    // Добавляем рёбра
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    // Отображаем граф
    g.printGraph();

    // Проверка на Эйлеров цикл
    vector<int> eulerCycle = g.getEulerCycle();
    if (!eulerCycle.empty()) {
        cout << "Эйлеров цикл найден: ";
        for (int vertex : eulerCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Эйлеров цикл не найден.\n";
    }

    // Проверка на Гамильтонов цикл
    vector<int> hamiltonCycle = g.getHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Гамильтонов цикл найден: ";
        for (int vertex : hamiltonCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Гамильтонов цикл не найден.\n";
    }

    // Построение остовного дерева
    Graph spanningTree = g.createSpanningTree();
    cout << "Остовное дерево:\n";
    spanningTree.printGraph();

    return 0;
}


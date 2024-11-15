#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {
private:
    struct Vertex {
        int id;
        list<int> neighbors;
    };

    vector<Vertex> vertices;

    // Проверка, существует ли Эйлеров цикл
    bool hasEulerianCycle() const {
        for (const auto& vertex : vertices) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    // Рекурсивная функция для поиска Гамильтонова цикла
    bool searchHamiltonianCycle(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == vertices.size()) {
            return path.front() == path.back();
        }

        for (int neighbor : vertices[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;

                if (searchHamiltonianCycle(neighbor, depth + 1, path, visited)) {
                    return true;
                }

                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    // Добавление нового узла
    void addVertex(int id) {
        vertices.push_back({id, {}});
    }

    // Добавление рёбер (неориентированный граф)
    void addEdge(int start, int end) {
        vertices[start].neighbors.push_back(end);
        vertices[end].neighbors.push_back(start);
    }

    // Вывод графа
    void displayGraph() const {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.id << ": ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Получение Эйлерова цикла
    vector<int> findEulerianCycle() {
        vector<int> cycle;
        if (!hasEulerianCycle()) return cycle;

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
            } else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    // Получение Гамильтонова цикла
    vector<int> findHamiltonianCycle() {
        vector<int> path(vertices.size(), -1);
        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        path[0] = 0;

        if (searchHamiltonianCycle(0, 1, path, visited)) {
            return path;
        }
        return {};
    }

    // Построение остовного дерева (используя BFS)
    Graph constructSpanningTree() const {
        Graph tree;
        for (int i = 0; i < vertices.size(); ++i) {
            tree.addVertex(i);
        }

        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(current, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }
};

int main() {
    Graph g;

    // Добавляем вершины
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    // Добавляем рёбра
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    // Выводим граф
    cout << "Graph structure:\n";
    g.displayGraph();

    // Проверка на Эйлеров цикл
    vector<int> eulerCycle = g.findEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int vertex : eulerCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "No Eulerian cycle found.\n";
    }

    // Проверка на Гамильтонов цикл
    vector<int> hamiltonCycle = g.findHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int vertex : hamiltonCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "No Hamiltonian cycle found.\n";
    }

    // Построение остовного дерева
    Graph spanningTree = g.constructSpanningTree();
    cout << "Spanning Tree structure:\n";
    spanningTree.displayGraph();

    return 0;
}
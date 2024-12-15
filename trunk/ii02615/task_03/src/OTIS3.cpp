#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Vertex {
    int id;
    vector<int> neighbors;
};

class Graph {
public:
    vector<Vertex> vertices;

    void addVertex(int id) {
        vertices.push_back({ id, {} });
    }

    void addEdge(int from, int to) {
        vertices[from].neighbors.push_back(to);
        vertices[to].neighbors.push_back(from);
    }

    void visualize() {
        for (int i = 0; i < vertices.size(); ++i) {
            cout << "Вершина " << vertices[i].id << ": ";
            for (int neighbor : vertices[i].neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> findEulerianCycle() {
        vector<int> cycle;
        if (!isEulerian()) {
            return cycle;
        }
        vector<bool> visited(vertices.size(), false);
        int startVertex = 0; // Выбираем стартовую вершину

        cycle.push_back(startVertex);
        visited[startVertex] = true;

        int currentVertex = startVertex;
        while (!cycle.empty()) {
            bool foundNeighbor = false;
            for (int i = 0; i < vertices[currentVertex].neighbors.size(); ++i) {
                int neighbor = vertices[currentVertex].neighbors[i];
                if (!visited[neighbor]) {
                    foundNeighbor = true;
                    visited[neighbor] = true;
                    currentVertex = neighbor;
                    cycle.push_back(currentVertex);
                    break;
                }
            }
            if (!foundNeighbor) {
                cycle.pop_back();
                if (!cycle.empty()) {
                    currentVertex = cycle.back();
                }
            }
        }
        return cycle;
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visited(vertices.size(), false);
        visited[0] = true; // Помечаем начальную вершину как посещенную
        cycle.push_back(0);

        if (!hasHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return cycle;
    }

    Graph constructSpanningTree() {
        Graph spanningTree;
        for (int i = 0; i < vertices.size(); ++i) {
            spanningTree.addVertex(i);
        }
        vector<bool> visited(vertices.size(), false);

        visited[0] = true;
        queue<int> nodeQueue;
        nodeQueue.push(0);

        while (!nodeQueue.empty()) {
            int currentNode = nodeQueue.front();
            nodeQueue.pop();

            for (int neighbor : vertices[currentNode].neighbors) {
                if (!visited[neighbor]) {
                    spanningTree.addEdge(currentNode, neighbor);
                    visited[neighbor] = true;
                    nodeQueue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }

private:
    bool isEulerian() {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool hasHamiltonianCycle(int currentVertex, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == vertices.size()) {
            if (cycle[0] == cycle[depth - 1]) {
                return true;
            }
            return false;
        }
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[currentVertex].neighbors[i] == 1 && !visited[i]) {
                visited[i] = true;
                cycle[depth] = i;
                if (hasHamiltonianCycle(i, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[i] = false; // Отменяем посещение для следующей итерации
            }
        }
        return false;
    }
};

int main() {
    Graph graph;

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    graph.visualize();

    if (vector<int> eulerianCycle = graph.findEulerianCycle(); !eulerianCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int vertex : eulerianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит Эйлерова цикла." << endl;
    }

    vector<int> hamiltonianCycle = graph.findHamiltonianCycle();
    if (vector<int> newHamiltonianCycle = graph.findHamiltonianCycle(); !newHamiltonianCycle.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int vertex : hamiltonianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит Гамильтонова цикла." << endl;
    }
    Graph spanningTree = graph.constructSpanningTree();
    spanningTree.visualize();
    return 0;
}

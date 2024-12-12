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

    bool hasEvenDegree() const {
        for (const auto& node : nodes) {
            if (node.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonianCycle(int currentNode, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return cycle.front() == cycle.back();
        }

        for (int neighbor : nodes[currentNode].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle[depth] = neighbor;
                if (findHamiltonianCycle(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        nodes[start].neighbors.push_back(end);
        nodes[end].neighbors.push_back(start);
    }

    void displayGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int neighbor : node.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!hasEvenDegree()) return cycle;

        vector<bool> visited(nodes.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int currentNode = stack.back();
            if (!nodes[currentNode].neighbors.empty()) {
                int nextNeighbor = nodes[currentNode].neighbors.front();
                stack.push_back(nextNeighbor);
                nodes[currentNode].neighbors.remove(nextNeighbor);
                nodes[nextNeighbor].neighbors.remove(currentNode);
            } else {
                cycle.push_back(currentNode);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        cycle[0] = 0;

        if (findHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph getSpanningTree() const {
        Graph spanningTree;
        for (int i = 0; i < nodes.size(); ++i) {
            spanningTree.addNode(i);
        }

        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int currentNode = queue.front();
            queue.pop();

            for (int neighbor : nodes[currentNode].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    spanningTree.addEdge(currentNode, neighbor);
                    queue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    Graph graph;

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
    graph.displayGraph();

    vector<int> eulerCycle = graph.getEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Эйлеров цикл не найден.\n";
    }

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Гамильтонов цикл не найден.\n";
    }

    Graph spanningTree = graph.getSpanningTree();
    cout << "Создание структуры дерева:\n";
    spanningTree.displayGraph();

    return 0;
}
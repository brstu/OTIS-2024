#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<int> adjList;
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void connectNodes(int source, int target) {
        nodes[source].adjList.push_back(target);
        nodes[target].adjList.push_back(source);
    }

    void display() {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (const auto& neighbor : node.adjList) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!checkEulerian()) {
            return cycle;
        }
        vector<bool> visited(nodes.size(), false);
        int startNode = 0;

        cycle.push_back(startNode);
        visited[startNode] = true;

        int currentNode = startNode;
        while (!cycle.empty()) {
            bool hasNeighbor = false;
            for (const auto& neighbor : nodes[currentNode].adjList) {
                if (!visited[neighbor]) {
                    hasNeighbor = true;
                    visited[neighbor] = true;
                    currentNode = neighbor;
                    cycle.push_back(currentNode);
                    break;
                }
            }
            if (!hasNeighbor) {
                cycle.pop_back();
                if (!cycle.empty()) {
                    currentNode = cycle.back();
                }
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        cycle.push_back(0);

        if (!findHamiltonian(0, 1, cycle, visited)) {
            return {};
        }
        return cycle;
    }

    Graph createSpanningTree() {
        Graph tree;
        for (int i = 0; i < nodes.size(); ++i) {
            tree.addNode(i);
        }
        vector<bool> visited(nodes.size(), false);

        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (const auto& neighbor : nodes[current].adjList) {
                if (!visited[neighbor]) {
                    tree.connectNodes(current, neighbor);
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool checkEulerian() {
        for (const auto& node : nodes) {
            if (node.adjList.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonian(int current, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return cycle[0] == cycle.back();
        }
        for (const auto& neighbor : nodes[current].adjList) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle.push_back(neighbor);
                if (findHamiltonian(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[neighbor] = false;
                cycle.pop_back();
            }
        }
        return false;
    }
};

int main() {
    Graph graph;

    for (int i = 0; i < 5; ++i) {
        graph.addNode(i);
    }

    graph.connectNodes(0, 1);
    graph.connectNodes(1, 2);
    graph.connectNodes(2, 3);
    graph.connectNodes(3, 4);
    graph.connectNodes(4, 0);

    graph.display();

    vector<int> eulerianCycle = graph.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian Cycle: ";
        for (const auto& node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Eulerian Cycle found." << endl;
    }

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (const auto& node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Hamiltonian Cycle found." << endl;
    }

    Graph spanningTree = graph.createSpanningTree();
    spanningTree.display();

    return 0;
}

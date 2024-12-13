#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<int> neighbors;
};

class Graph {
public:
    vector<Node> nodes;

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

    vector<int> findEulerianCycle() const {
        if (!isEulerian()) {
            return {};
        }

        vector<int> cycle;
        vector<bool> visitedNodes(nodes.size(), false);
        int startNode = 0;

        dfsEulerianCycle(startNode, visitedNodes, cycle);

        return cycle;
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        cycle[0] = 0;
        visited[0] = true;

        if (hamiltonianHelper(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph generateSpanningTree() const {
        Graph spanningTree;
        for (const auto& node : nodes) {
            spanningTree.addNode(node.id);
        }

        vector<bool> visited(nodes.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : nodes[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    spanningTree.addEdge(current, neighbor);
                    q.push(neighbor);
                }
            }
        }

        return spanningTree;
    }

private:
    bool isEulerian() const {
        for (const auto& node : nodes) {
            if (node.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    void dfsEulerianCycle(int node, vector<bool>& visited, vector<int>& cycle) const {
        visited[node] = true;
        cycle.push_back(node);

        for (int neighbor : nodes[node].neighbors) {
            if (!visited[neighbor]) {
                dfsEulerianCycle(neighbor, visited, cycle);
            }
        }
    }

    bool hamiltonianHelper(int current, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            // Check if it forms a cycle
            for (int neighbor : nodes[current].neighbors) {
                if (neighbor == cycle[0]) {
                    return true;
                }
            }
            return false;
        }

        for (int neighbor : nodes[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle[depth] = neighbor;

                if (hamiltonianHelper(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }

                visited[neighbor] = false;
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

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    cout << "Graph structure:" << endl;
    graph.displayGraph();

    vector<int> eulerianCycle = graph.findEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Eulerian cycle found." << endl;
    }

    vector<int> hamiltonianCycle = graph.findHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Hamiltonian cycle found." << endl;
    }

    Graph spanningTree = graph.generateSpanningTree();
    cout << "Spanning tree:" << endl;
    spanningTree.displayGraph();

    return 0;
}
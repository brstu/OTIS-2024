#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> // For std::find

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
        if (start >= 0 && start < nodes.size() && end >= 0 && end < nodes.size()) {
            if (std::find(nodes[start].neighbors.begin(), nodes[start].neighbors.end(), end) == nodes[start].neighbors.end()) {
                nodes[start].neighbors.push_back(end);
                nodes[end].neighbors.push_back(start);
            }
        }
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
        vector<vector<int>> edgeVisited(nodes.size(), vector<int>(nodes.size(), false));
        eulerianDFS(0, edgeVisited, cycle);
        return cycle;
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle(nodes.size() + 1, -1); // Include space for cycle closure
        vector<bool> visited(nodes.size(), false);
        cycle[0] = 0;
        visited[0] = true;

        if (hamiltonianDFS(0, 1, cycle, visited)) {
            cycle[nodes.size()] = cycle[0]; // Close the cycle
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
            // Check all vertices have even degree and the graph is connected
            if (!isConnected()) {
                return false;
            }
        for (const auto& node : nodes) {
            if (node.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    void eulerianDFS(int node, vector<vector<int>>& edgeVisited, vector<int>& cycle) const {
        for (int neighbor : nodes[node].neighbors) {
            if (!edgeVisited[node][neighbor]) {
                edgeVisited[node][neighbor] = true;
                edgeVisited[neighbor][node] = true; // Since the graph is undirected
                eulerianDFS(neighbor, edgeVisited, cycle);
            }
        }
        cycle.push_back(node);
    }

    bool hamiltonianDFS(int current, int depth, vector<int>& cycle, vector<bool>& visited) {
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

                if (hamiltonianDFS(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }

                visited[neighbor] = false;
            }
        }

        return false;
    }

    bool isConnected() const {
        vector<bool> visited(nodes.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        int count = 0;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            ++count;

            for (int neighbor : nodes[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return count == nodes.size();
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

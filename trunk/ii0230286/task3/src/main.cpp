#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class GraphStructure {
private:
    struct Node {
        int id;
        list<int> connections;
    };

    vector<Node> nodes;

    // Check if there exists an Eulerian cycle
    bool hasEulerianCircuit() const {
        for (const auto& node : nodes) {
            if (node.connections.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    // Recursive function for Hamiltonian cycle search
    bool searchHamiltonianCircuit(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return path.front() == path.back();
        }

        for (int neighbor : nodes[current].connections) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;

                if (searchHamiltonianCircuit(neighbor, depth + 1, path, visited)) {
                    return true;
                }

                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    // Add a new node
    void addNode(int id) {
        nodes.push_back({id, {}});
    }

    // Add edges (undirected graph)
    void addEdge(int start, int end) {
        nodes[start].connections.push_back(end);
        nodes[end].connections.push_back(start);
    }

    // Display the graph
    void displayGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int connection : node.connections) {
                cout << connection << " ";
            }
            cout << endl;
        }
    }

    // Get the Eulerian cycle
    vector<int> findEulerianCircuit() {
        vector<int> circuit;
        if (!hasEulerianCircuit()) return circuit;

        vector<bool> visited(nodes.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!nodes[current].connections.empty()) {
                int next = nodes[current].connections.front();
                stack.push_back(next);
                nodes[current].connections.remove(next);
                nodes[next].connections.remove(current);
            } else {
                circuit.push_back(current);
                stack.pop_back();
            }
        }
        return circuit;
    }

    // Get the Hamiltonian cycle
    vector<int> findHamiltonianCircuit() {
        vector<int> path(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        path[0] = 0;

        if (searchHamiltonianCircuit(0, 1, path, visited)) {
            return path;
        }
        return {};
    }

    // Construct a spanning tree (using BFS)
    GraphStructure constructSpanningTree() const {
        GraphStructure tree;
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

            for (int connection : nodes[current].connections) {
                if (!visited[connection]) {
                    visited[connection] = true;
                    tree.addEdge(current, connection);
                    q.push(connection);
                }
            }
        }
        return tree;
    }
};

int main() {
    GraphStructure g;

    // Add nodes
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    // Display the graph
    cout << "Graph structure:\n";
    g.displayGraph();

    // Check for Eulerian cycle
    vector<int> eulerCircuit = g.findEulerianCircuit();
    if (!eulerCircuit.empty()) {
        cout << "Eulerian circuit: ";
        for (int node : eulerCircuit) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Eulerian circuit found.\n";
    }

    // Check for Hamiltonian cycle
    vector<int> hamiltonCircuit = g.findHamiltonianCircuit();
    if (!hamiltonCircuit.empty()) {
        cout << "Hamiltonian circuit: ";
        for (int node : hamiltonCircuit) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Hamiltonian circuit found.\n";
    }

    // Construct a spanning tree
    GraphStructure spanningTree = g.constructSpanningTree();
    cout << "Spanning Tree structure:\n";
    spanningTree.displayGraph();

    return 0;
}
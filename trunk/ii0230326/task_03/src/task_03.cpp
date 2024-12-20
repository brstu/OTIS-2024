#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

struct Node {
    int id;
    vector<int> adjacentNodes;
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        nodes[start].adjacentNodes.push_back(end);
        nodes[end].adjacentNodes.push_back(start);
    }

    void displayGraph() {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int neighbor : node.adjacentNodes) {
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
        vector<bool> visited(nodes.size(), false);
        int currentNode = 0;

        cycle.push_back(currentNode);
        visited[currentNode] = true;

        while (!cycle.empty()) {
            bool hasUnvisitedNeighbor = false;
            for (int neighbor : nodes[currentNode].adjacentNodes) {
                if (!visited[neighbor]) {
                    hasUnvisitedNeighbor = true;
                    visited[neighbor] = true;
                    cycle.push_back(neighbor);
                    currentNode = neighbor;
                    break;
                }
            }
            if (!hasUnvisitedNeighbor) {
                currentNode = cycle.back();
                cycle.pop_back();
            }
        }
        return cycle;
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle;
        unordered_set<int> visited;
        visited.insert(0);
        cycle.push_back(0);

        if (searchHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph generateSpanningTree() {
        Graph spanningTree;
        for (int i = 0; i < nodes.size(); ++i) {
            spanningTree.addNode(i);
        }
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;

        queue<int> nodeQueue;
        nodeQueue.push(0);

        while (!nodeQueue.empty()) {
            int currentNode = nodeQueue.front();
            nodeQueue.pop();

            for (int neighbor : nodes[currentNode].adjacentNodes) {
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
        for (const auto& node : nodes) {
            if (node.adjacentNodes.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool searchHamiltonianCycle(int currentNode, int depth, vector<int>& cycle, unordered_set<int>& visited) {
        if (depth == nodes.size()) {
            return cycle.front() == cycle.back();
        }
        for (int neighbor : nodes[currentNode].adjacentNodes) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                cycle.push_back(neighbor);
                if (searchHamiltonianCycle(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }
                cycle.pop_back(); // backtrack
                visited.erase(neighbor); // unmark
            }
        }
        return false;
    }
};

int main() {
    Graph graph;

    // Adding nodes
    for (int i = 0; i < 5; ++i) {
        graph.addNode(i);
    }

    // Adding edges
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    graph.displayGraph();

    // Finding Eulerian cycle
    vector<int> eulerianCycle = graph.findEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "The graph does not contain an Eulerian cycle." << endl;
    }

    // Finding Hamiltonian cycle
    vector<int> hamiltonianCycle = graph.findHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "The graph does not contain a Hamiltonian cycle." << endl;
    }

    // Generating spanning tree
    Graph spanningTree = graph.generateSpanningTree();
    spanningTree.displayGraph();

    return 0;
}
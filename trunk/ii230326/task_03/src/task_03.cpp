#include <iostream>
#include <queue>
#include <vector>

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

    void showGraph() {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int neighbor : node.adjacentNodes) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!isEulerian()) {
            return cycle;
        }
        vector<bool> visitedNodes(nodes.size(), false);
        int startingNode = 0;

        cycle.push_back(startingNode);
        visitedNodes[startingNode] = true;

        int currentNode = startingNode;
        while (!cycle.empty()) {
            bool foundNeighbor = false;
            for (int neighbor : nodes[currentNode].adjacentNodes) {
                if (!visitedNodes[neighbor]) {
                    foundNeighbor = true;
                    visitedNodes[neighbor] = true;
                    cycle.push_back(neighbor);
                    currentNode = neighbor;
                    break;
                }
            }
            if (!foundNeighbor) {
                currentNode = cycle.back();
                cycle.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visitedNodes(nodes.size(), false);
        visitedNodes[0] = true;
        cycle.push_back(0);

        if (findHamiltonianCycle(0, 1, cycle, visitedNodes)) {
            return cycle;
        }
        return {};
    }

    Graph getSpanningTree() {
        Graph spanningTree;
        for (int i = 0; i < nodes.size(); ++i) {
            spanningTree.addNode(i);
        }
        vector<bool> visitedNodes(nodes.size(), false);
        visitedNodes[0] = true;

        queue<int> nodeQueue;
        nodeQueue.push(0);

        while (!nodeQueue.empty()) {
            int currentNode = nodeQueue.front();
            nodeQueue.pop();

            for (int neighbor : nodes[currentNode].adjacentNodes) {
                if (!visitedNodes[neighbor]) {
                    spanningTree.addEdge(currentNode, neighbor);
                    visitedNodes[neighbor] = true;
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

    bool findHamiltonianCycle(int currentNode, int depth, vector<int>& cycle, vector<bool>& visitedNodes) {
        if (depth == nodes.size()) {
            return cycle.front() == cycle.back();
        }
        for (int i = 0; i < nodes[currentNode].adjacentNodes.size(); ++i) {
            int nextNode = nodes[currentNode].adjacentNodes[i];
            if (!visitedNodes[nextNode]) {
                visitedNodes[nextNode] = true;
                cycle.push_back(nextNode);
                if (findHamiltonianCycle(nextNode, depth + 1, cycle, visitedNodes)) {
                    return true;
                }
                cycle.pop_back(); // backtrack
                visitedNodes[nextNode] = false;
            }
        }
        return false;
    }
};

int main() {
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

    graph.showGraph();

    vector<int> eulerianCycle = graph.getEulerianCycle();
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

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
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

    Graph spanningTree = graph.getSpanningTree();
    spanningTree.showGraph();
    return 0;
}
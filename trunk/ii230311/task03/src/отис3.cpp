#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int id;
    vector<int> edges;
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void addEdge(int startNode, int endNode) {
        nodes[startNode].edges.push_back(endNode);
        nodes[endNode].edges.push_back(startNode);
    }

    void displayGraph() {
        for (int index = 0; index < nodes.size(); ++index) {
            cout << "Node " << nodes[index].id << ": ";
            for (int neighbor : nodes[index].edges) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianPath() {
        vector<int> eulerPath;
        if (!isEulerian()) {
            return eulerPath;
        }
        vector<bool> visitedNodes(nodes.size(), false);
        int startNode = 0;
        eulerPath.push_back(startNode);
        visitedNodes[startNode] = true;

        int currentNode = startNode;
        while (!eulerPath.empty()) {
            bool foundNeighbor = false;
            for (int i = 0; i < nodes[currentNode].edges.size(); ++i) {
                int neighbor = nodes[currentNode].edges[i];
                if (!visitedNodes[neighbor]) {
                    foundNeighbor = true;
                    visitedNodes[neighbor] = true;
                    currentNode = neighbor;
                    eulerPath.push_back(currentNode);
                    break;
                }
            }
            if (!foundNeighbor) {
                eulerPath.pop_back();
                if (!eulerPath.empty()) {
                    currentNode = eulerPath.back();
                }
            }
        }
        return eulerPath;
    }

    vector<int> getHamiltonianPath() {
        vector<int> hamiltonPath;
        vector<bool> visitedNodes(nodes.size(), false);
        visitedNodes[0] = true;
        hamiltonPath.push_back(0);

        if (!searchHamiltonianPath(0, 1, hamiltonPath, visitedNodes)) {
            return {};
        }
        return hamiltonPath;
    }

    Graph createSpanningTree() {
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
            for (int neighbor : nodes[currentNode].edges) {
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
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i].edges.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool searchHamiltonianPath(int currentNode, int depth, vector<int>& hamiltonPath, vector<bool>& visitedNodes) {
        if (depth == nodes.size()) {
            return hamiltonPath[0] == currentNode;
        }
        for (int neighbor : nodes[currentNode].edges) {
            if (!visitedNodes[neighbor]) {
                visitedNodes[neighbor] = true;
                hamiltonPath.push_back(neighbor);
                if (searchHamiltonianPath(neighbor, depth + 1, hamiltonPath, visitedNodes)) {
                    return true;
                }
                hamiltonPath.pop_back();
                visitedNodes[neighbor] = false;
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "rus");
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

    graph.displayGraph();

    vector<int> eulerianPath = graph.getEulerianPath();
    if (!eulerianPath.empty()) {
        cout << "Эйлеров путь: ";
        for (int node : eulerianPath) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит эйлерова пути." << endl;
    }

    vector<int> hamiltonianPath = graph.getHamiltonianPath();
    if (!hamiltonianPath.empty()) {
        cout << "Гамильтонов путь: ";
        for (int node : hamiltonianPath) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит гамильтонова пути." << endl;
    }

    Graph spanningTree = graph.createSpanningTree();
    spanningTree.displayGraph();

    return 0;
}
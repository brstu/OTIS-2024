#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

class Graph {
private:
    struct Node {
        int id;
        list<int> adj; 
    };

    vector<Node> nodes;

    bool isEulerian() const {
        for (const auto& node : nodes) {
            if (node.adj.size() % 2 != 0) return false;
        }
        return true;
    }

    bool hamiltonianPathUtil(int current, vector<int>& path, vector<bool>& visited, int depth) {
        if (depth == nodes.size()) {
            return path.front() == path.back(); 
        }

        for (int neighbor : nodes[current].adj) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;

                if (hamiltonianPathUtil(neighbor, path, visited, depth + 1)) {
                    return true;
                }

                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    void insertVertex(int id) {
        nodes.push_back({ id, {} });
    }

    void insertEdge(int u, int v) {
        nodes[u].adj.push_back(v);
        nodes[v].adj.push_back(u);
    }

    void printGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << " -> ";
            for (int neighbor : node.adj) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> eulerCycle;
        if (!isEulerian()) return eulerCycle;

        vector<list<int>> adjCopy(nodes.size());
        for (size_t i = 0; i < nodes.size(); ++i) {
            adjCopy[i] = nodes[i].adj;
        }

        stack<int> dfsStack;
        dfsStack.push(0);

        while (!dfsStack.empty()) {
            int current = dfsStack.top();
            if (!adjCopy[current].empty()) {
                int next = adjCopy[current].front();
                dfsStack.push(next);
                adjCopy[current].remove(next);
                adjCopy[next].remove(current);
            }
            else {
                eulerCycle.push_back(current);
                dfsStack.pop();
            }
        }
        return eulerCycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> path(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);

        path[0] = 0;
        visited[0] = true;

        if (hamiltonianPathUtil(0, path, visited, 1)) {
            return path;
        }
        return {};
    }

    Graph buildSpanningTree() const {
        Graph tree;
        for (size_t i = 0; i < nodes.size(); ++i) {
            tree.insertVertex(i);
        }

        vector<bool> visited(nodes.size(), false);
        queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : nodes[current].adj) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.insertEdge(current, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }
};

int main() {
    Graph graph;

    for (int i = 0; i <= 4; ++i) {
        graph.insertVertex(i);
    }

    graph.insertEdge(0, 1);
    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(3, 4);
    graph.insertEdge(4, 0);

    cout << "Graph structure:\n";
    graph.printGraph();

    vector<int> eulerianCycle = graph.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian Cycle: ";
        for (int node : eulerianCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Eulerian Cycle exists.\n";
    }

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (int node : hamiltonianCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Hamiltonian Cycle exists.\n";
    }

    Graph spanningTree = graph.buildSpanningTree();
    cout << "Spanning Tree structure:\n";
    spanningTree.printGraph();

    return 0;
}
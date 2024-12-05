#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjList;

public:
    explicit Graph(int size) : adjList(size) {} //explicit constructor

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() const {
        for (size_t i = 0; i < adjList.size(); ++i) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    bool hasEulerianCycle() const {
        return all_of(adjList.begin(), adjList.end(), [](const auto& vec) { return vec.size() % 2 == 0; });
    }

    vector<int> findEulerianCycle() const {
        if (!hasEulerianCycle()) { return {}; } //Added Braces for clarity
        vector<vector<int>> tempAdj = adjList;
        vector<int> cycle;
        vector<int> stack = { 0 };

        while (!stack.empty()) {
            int v = stack.back();
            if (!tempAdj[v].empty()) {
                int u = tempAdj[v].back();
                tempAdj[v].pop_back();
                auto it = remove(tempAdj[u].begin(), tempAdj[u].end(), v);
                tempAdj[u].erase(it, tempAdj[u].end());
                stack.push_back(u);
            }
            else {
                cycle.push_back(v);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> findHamiltonianCycle() const {
        vector<int> path = { 0 };
        vector<bool> visited(adjList.size(), false);
        visited[0] = true;
        if (hamiltonianDFS(0, path, visited)) { return path; } //Added Braces for clarity
        return {};
    }

    Graph buildSpanningTree() const {
        Graph tree(adjList.size());
        vector<bool> visited(adjList.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            visited[curr] = true;
            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor]) {
                    tree.addEdge(curr, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool hamiltonianDFS(int node, vector<int>& path, vector<bool>& visited) const {
        if (path.size() == adjList.size()) { return find(adjList[node].begin(), adjList[node].end(), path[0]) != adjList[node].end(); } //Added Braces for clarity
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                if (hamiltonianDFS(neighbor, path, visited)) { return true; } //Added Braces for clarity
                path.pop_back();
                visited[neighbor] = false;
            }
        }
        return false;
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    graph.printGraph();
    auto eulerCycle = graph.findEulerianCycle();
    cout << (eulerCycle.empty() ? "No Eulerian Cycle found.n" : "Eulerian Cycle: ");
    for (int node : eulerCycle) cout << node << " ";
    cout << endl;

    auto hamiltonCycle = graph.findHamiltonianCycle();
    cout << (hamiltonCycle.empty() ? "No Hamiltonian Cycle found.n" : "Hamiltonian Cycle: ");
    for (int node : hamiltonCycle) cout << node << " ";
    cout << endl;

    auto spanningTree = graph.buildSpanningTree();
    cout << "Spanning Tree:n";
    spanningTree.printGraph();
    return 0;
}

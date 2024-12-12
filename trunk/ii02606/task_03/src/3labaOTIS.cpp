#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
    vector<vector<int>> adjList;

public:
    Graph(int size) : adjList(size) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() const {
        for (int i = 0; i < adjList.size(); ++i) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    bool hasEulerianCycle() const {
        for (const auto& neighbors : adjList) {
            if (neighbors.size() % 2 != 0) return false;
        }
        return true;
    }

    vector<int> findEulerianCycle() const {
        if (!hasEulerianCycle()) return {};
        vector<vector<int>> tempAdj = adjList;
        vector<int> cycle, stack = { 0 };

        while (!stack.empty()) {
            int v = stack.back();
            if (!tempAdj[v].empty()) {
                int u = tempAdj[v].back();
                tempAdj[v].pop_back();
                tempAdj[u].erase(find(tempAdj[u].begin(), tempAdj[u].end(), v));
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

        if (hamiltonianDFS(0, path, visited)) return path;
        return {};
    }

    Graph buildSpanningTree() const {
        Graph tree(adjList.size());
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(curr, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool hamiltonianDFS(int node, vector<int>& path, vector<bool>& visited) const {
        if (path.size() == adjList.size()) {
            return find(adjList[node].begin(), adjList[node].end(), path[0]) != adjList[node].end();
        }

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                if (hamiltonianDFS(neighbor, path, visited)) return true;
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
    if (!eulerCycle.empty()) {
        cout << "Eulerian Cycle: ";
        for (int node : eulerCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Eulerian Cycle found." << endl;
    }

    auto hamiltonCycle = graph.findHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (int node : hamiltonCycle) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No Hamiltonian Cycle found." << endl;
    }

    auto spanningTree = graph.buildSpanningTree();
    cout << "Spanning Tree:" << endl;
    spanningTree.printGraph();

    return 0;
}

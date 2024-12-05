#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept> // for std::invalid_argument

using namespace std;

class Graph {
private:
    vector<vector<int>> adjList;
    int numVertices;

public:
    explicit Graph(int size) : adjList(size), numVertices(size) {
        if (size < 0) {
            throw invalid_argument("Graph size cannot be negative.");
        }
    }

    void addEdge(int u, int v) {
        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
            throw out_of_range("Vertex index out of range");
        }
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
        if (!isConnected()) return false; //Crucial connectivity check
        for (const auto& neighbors : adjList) {
            if (neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    vector<int> findEulerianCycle() const {
        if (!hasEulerianCycle()) {
            return {};
        }
        vector<vector<int>> tempAdj = adjList;
        vector<int> cycle;
        vector<int> stack;
        stack.push_back(0); //Start at node 0 (you could improve this by selecting a node with higher degree)

        while (!stack.empty()) {
            int v = stack.back();
            if (!tempAdj[v].empty()) {
                int u = tempAdj[v].back();
                tempAdj[v].pop_back();
                auto it = find(tempAdj[u].begin(), tempAdj[u].end(), v);
                if (it != tempAdj[u].end()) {
                    tempAdj[u].erase(it);
                }
                stack.push_back(u);
            }
            else {
                cycle.push_back(v);
                stack.pop_back();
            }
        }
        reverse(cycle.begin(), cycle.end()); //Correct order
        return cycle;
    }

    vector<int> findHamiltonianCycle() const {
        //This algorithm is still inefficient (exponential time complexity).  Consider better algorithms for larger graphs.
        vector<int> path = { 0 };
        vector<bool> visited(adjList.size(), false);
        visited[0] = true;
        if (hamiltonianDFS(0, path, visited)) {
            return path;
        }
        return {};
    }

    Graph buildSpanningTree() const {
        //This creates a spanning tree, but not necessarily a minimum spanning tree. Consider Prim's or Kruskal's for that.
        Graph tree(adjList.size());
        vector<bool> visited(adjList.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
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
    bool isConnected() const {
        if (numVertices == 0) return true; //Empty graph is connected
        vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int count = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            count++;
            for (int v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return count == numVertices;
    }

    bool hamiltonianDFS(int node, vector<int>& path, vector<bool>& visited) const {
        if (path.size() == adjList.size()) {
            return find(adjList[node].begin(), adjList[node].end(), path[0]) != adjList[node].end();
        }
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                if (hamiltonianDFS(neighbor, path, visited)) {
                    return true;
                }
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
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Eulerian Cycle found." << endl;
    }

    auto hamiltonCycle = graph.findHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (int node : hamiltonCycle) {
            cout << node << " ";
        }
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


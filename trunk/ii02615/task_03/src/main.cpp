#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {
private:
    struct Node {
        int id;
        list<int> adjNodes;
    };

    vector<Node> nodes;

    bool isEvenDegree() const {
        for (const auto& node : nodes) {
            if (node.adjNodes.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonianCycle(int node, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return cycle.front() == cycle.back();
        }

        for (int adj : nodes[node].adjNodes) {
            if (!visited[adj]) {
                visited[adj] = true;
                cycle[depth] = adj;
                if (findHamiltonianCycle(adj, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[adj] = false;
            }
        }
        return false;
    }

public:
    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        nodes[start].adjNodes.push_back(end);
        nodes[end].adjNodes.push_back(start);
    }

    void showGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int nei : node.adjNodes) {
                cout << nei << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!isEvenDegree()) return cycle;

        vector<bool> visited(nodes.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int cur = stack.back();
            if (!nodes[cur].adjNodes.empty()) {
                int next = nodes[cur].adjNodes.front();
                stack.push_back(next);
                nodes[cur].adjNodes.remove(next);
                nodes[next].adjNodes.remove(cur);
            } else {
                cycle.push_back(cur);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        cycle[0] = 0;

        if (findHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph getSpanningTree() const {
        Graph spanningTree;
        for (int i = 0; i < nodes.size(); ++i) {
            spanningTree.addNode(i);
        }

        vector<bool> visited(nodes.size(), false);
        visited[0] = true;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nei : nodes[cur].adjNodes) {
                if (!visited[nei]) {
                    visited[nei] = true;
                    spanningTree.addEdge(cur, nei);
                    q.push(nei);
                }
            }
        }
        return spanningTree;
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    Graph g;

    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    cout << "Структура графа:\n";
    g.showGraph();

    vector<int> eulerCycle = g.getEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Эйлеров цикл не найден.\n";
    }

    vector<int> hamiltonianCycle = g.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Гамильтонов цикл не найден.\n";
    }

    Graph spanningTree = g.getSpanningTree();
    cout << "Создание структуры дерева:\n";
    spanningTree.showGraph();

    return 0;
}
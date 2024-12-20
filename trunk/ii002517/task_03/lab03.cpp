#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graf {
public:
    struct vert {
        int id;
        list<int> neighbors;
    };

    vector<vert> verts;

    bool isEulerian() const {
        for (const auto& vertex : verts) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonian(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == verts.size()) {
            return path.front() == path.back();
        }

        for (int neighbor : verts[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;
                if (findHamiltonian(neighbor, depth + 1, path, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

    void addVertex(int id) {
        verts.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        verts[start].neighbors.push_back(end);
        verts[end].neighbors.push_back(start);
    }

    void printGraph() const {
        cout << "Граф:\n";
        for (const auto& vertex : verts) {
            cout << "Вершина " << vertex.id << " соединена с: ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    vector<int> getEulerCycle() {
        vector<int> cycle;
        if (!isEulerian()) return cycle;

        vector<bool> visited(verts.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!verts[current].neighbors.empty()) {
                int next = verts[current].neighbors.front();
                stack.push_back(next);
                verts[current].neighbors.remove(next);
                verts[next].neighbors.remove(current);
            }
            else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(verts.size(), -1);
        vector<bool> visited(verts.size(), false);
        visited[0] = true;
        cycle[0] = 0;

        if (findHamiltonian(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graf createSpanningTree() const {
        Graf tree;
        for (int i = 0; i < verts.size(); ++i) {
            tree.addVertex(i);
        }

        vector<bool> visited(verts.size(), false);
        queue<int> bfsQueue;
        visited[0] = true;
        bfsQueue.push(0);

        while (!bfsQueue.empty()) {
            int current = bfsQueue.front();
            bfsQueue.pop();

            for (int neighbor : verts[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(current, neighbor);
                    bfsQueue.push(neighbor);
                }
            }
        }
        return tree;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graf graf;


    for (int i = 0; i < 5; ++i) {
        graf.addVertex(i);
    }

    graf.addEdge(0, 1);
    graf.addEdge(1, 2);
    graf.addEdge(2, 3);
    graf.addEdge(3, 4);
    graf.addEdge(4, 0);
    graf.printGraph();

    vector<int> eulerCycle = graf.getEulerCycle();
    if (!eulerCycle.empty()) {
        cout << "Эйлеров цикл выглядит так: ";
        for (int vertex : eulerCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Не найден эйлеров цикл.\n";
    }

    vector<int> hamiltonCycle = graf.getHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Гамильтонов цикл выглядит так: ";
        for (int vertex : hamiltonCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Не найден найден Гамельтонов.\n";
    }

    Graf Tree = graf.createSpanningTree();
    cout << "Остовное дерево выглядит так:\n";
    Tree.printGraph();

    return 0;
}
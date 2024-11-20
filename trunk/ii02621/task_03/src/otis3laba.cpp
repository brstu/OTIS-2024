#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class G {
private:
    struct N {
        int id;
        list<int> adjNodes;
    };

    vector<N> nodes;

    bool isE() const {
        for (const auto& node : nodes) {
            if (node.adjNodes.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }


    bool findH(int node, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return cycle.front() == cycle.back();
        }

        for (int adj : nodes[node].adjNodes) {
            if (!visited[adj]) {
                visited[adj] = true;
                cycle[depth] = adj;
                if (findH(adj, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[adj] = false;
            }
        }
        return false;
    }

public:
   
    void addN(int id) {
        nodes.push_back({ id, {} });
    }

  
    void addE(int start, int end) {
        nodes[start].adjNodes.push_back(end);
        nodes[end].adjNodes.push_back(start);
    }


    void showG() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int nei : node.adjNodes) {
                cout << nei << " ";
            }
            cout << endl;
        }
    }

    vector<int> getE() {
        vector<int> c;
        if (!isE()) return c;

        vector<bool> visited(nodes.size(), false);
        list<int> s;
        s.push_back(0);

        while (!s.empty()) {
            int cur = s.back();
            if (!nodes[cur].adjNodes.empty()) {
                int next = nodes[cur].adjNodes.front();
                s.push_back(next);
                nodes[cur].adjNodes.remove(next);
                nodes[next].adjNodes.remove(cur);
            }
            else {
                c.push_back(cur);
                s.pop_back();
            }
        }
        return c;
    }

 
    vector<int> getH() {
        vector<int> c(nodes.size(), -1);
        vector<bool> v(nodes.size(), false);
        v[0] = true;
        c[0] = 0;

        if (findH(0, 1, c, v)) {
            return c;
        }
        return {};
    }

    G getSpanningTree() const {
        G sT;
        for (int i = 0; i < nodes.size(); ++i) {
            sT.addN(i);
        }

        vector<bool> v(nodes.size(), false);
        v[0] = true;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nei : nodes[cur].adjNodes) {
                if (!v[nei]) {
                    v[nei] = true;
                    sT.addE(cur, nei);
                    q.push(nei);
                }
            }
        }
        return sT;
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    G g;


    g.addN(0);
    g.addN(1);
    g.addN(2);
    g.addN(3);
    g.addN(4);


    g.addE(0, 1);
    g.addE(1, 2);
    g.addE(2, 3);
    g.addE(3, 4);
    g.addE(4, 0);

    cout << "Структура графа:\n";
    g.showG();

    vector<int> eC = g.getE();
    if (!eC.empty()) {
        cout << "Эйлеров цикл: ";
        for (int node : eC) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Эйлеров цикл не найден.\n";
    }
    vector<int> hC = g.getH();
    if (!hC.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int node : hC) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Гамильтонов цикл не найден.\n";
    }
    G sT = g.getSpanningTree();
    cout << "Создание структуры дерева:\n";
    sT.showG();

    return 0;
}

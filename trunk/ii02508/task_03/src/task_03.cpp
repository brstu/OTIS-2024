#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
    int id;
    vector<int> adjnodes;
};

class graph {
public:
    vector<node> nodes;

    void add_node(int id) {
        nodes.push_back({ id, {} });
    }

    void add_edge(int start, int end) {
        nodes[start].adjnodes.push_back(end);
        nodes[end].adjnodes.push_back(start);
    }

    void show_graph() {
        for (int i = 0; i < nodes.size(); ++i) {
            cout << "Node " << nodes[i].id << ": ";
            for (int neighbor : nodes[i].adjnodes) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> get_eulerian_cycle() {
        vector<int> cycle;
        if (!is_eulerian()) {
            return cycle;
        }
        vector<bool> visitednodes(nodes.size(), false);
        int startnode = 0;

        cycle.push_back(startnode);
        visitednodes[startnode] = true;

        int curnode = startnode;
        while (!cycle.empty()) {
            bool found_neighbor = false;
            for (int i = 0; i < nodes[curnode].adjnodes.size(); ++i) {
                int neighbor = nodes[curnode].adjnodes[i];
                if (!visitednodes[neighbor]) {
                    found_neighbor = true;
                    visitednodes[neighbor] = true;
                    curnode = neighbor;
                    cycle.push_back(curnode);
                    break;
                }
            }
            if (!found_neighbor) {
                cycle.pop_back();
                if (!cycle.empty()) {
                    curnode = cycle.back();
                }
            }
        }
        return cycle;
    }

    vector<int> get_hamiltonian_cycle() {
        vector<int> cycle;
        vector<bool> visitednodes(nodes.size(), false);
        visitednodes[0] = true;
        cycle.push_back(0);

        if (!has_hamiltonian_cycle(0, 1, cycle, visitednodes)) {
            return cycle;
        }
        return cycle;
    }

    graph spanningtree() {
        graph spanningTree;
        for (int i = 0; i < nodes.size(); ++i) {
            spanningTree.add_node(i);
        }
        vector<bool> visitednodes(nodes.size(), false);

        visitednodes[0] = true;
        queue<int> nodeQueue;
        nodeQueue.push(0);

        while (!nodeQueue.empty()) {
            int curnode = nodeQueue.front();
            nodeQueue.pop();

            for (int neighbor : nodes[curnode].adjnodes) {
                if (!visitednodes[neighbor]) {
                    spanningTree.add_edge(curnode, neighbor);
                    visitednodes[neighbor] = true;
                    nodeQueue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }

private:
    bool is_eulerian() {
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[i].adjnodes.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool has_hamiltonian_cycle(int curnode, int depth, vector<int>& cycle, vector<bool>& visitednodes) {
        if (depth == nodes.size()) {
            if (cycle[0] == cycle[depth - 1]) {
                return true;
            }
            return false;
        }
        for (int i = 0; i < nodes.size(); ++i) {
            if (nodes[curnode].adjnodes[i] == 1 && !visitednodes[i]) {
                visitednodes[i] = true;
                cycle[depth] = i;
                if (has_hamiltonian_cycle(i, depth + 1, cycle, visitednodes)) {
                    return true;
                }
                visitednodes[i] = false;
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    graph gr;

    gr.add_node(0);
    gr.add_node(1);
    gr.add_node(2);
    gr.add_node(3);
    gr.add_node(4);

    gr.add_edge(0, 1);
    gr.add_edge(1, 2);
    gr.add_edge(2, 3);
    gr.add_edge(3, 4);
    gr.add_edge(4, 0);

    gr.show_graph();

    if (vector<int> eulerianCycle = gr.get_eulerian_cycle();  !eulerianCycle.empty()) {
        cout << "eulerian cycle: ";
        for (int node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "there is no eulerian cycle" << endl;
    }

    vector<int> hamiltonianCycle = gr.get_hamiltonian_cycle();
    if (vector<int> new_hamiltonian_cycle = gr.get_hamiltonian_cycle(); !new_hamiltonian_cycle.empty()) {
        cout << "hamiltonian cycle: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "there is no hamiltonian cycle" << endl;
    }
    graph spanningTree = gr.spanningtree();
    spanningTree.show_graph();
    return 0;
}
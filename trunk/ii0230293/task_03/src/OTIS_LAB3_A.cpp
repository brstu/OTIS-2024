#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Vertex {
    int index;
    vector<int> neighbors;
};

class Graph {
public:
    vector<Vertex> vertices;

    void insert_vertex(int index) {
        vertices.push_back({ index, {} });
    }

    void connect_vertices(int from, int to) {
        vertices[from].neighbors.push_back(to);
        vertices[to].neighbors.push_back(from);
    }

    void display() {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.index << ": ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> find_eulerian_cycle() {
        vector<int> path;
        if (!check_eulerian()) {
            return path;
        }
        vector<bool> visited(vertices.size(), false);
        int initial = 0;

        path.push_back(initial);
        visited[initial] = true;

        int current = initial;
        while (!path.empty()) {
            bool found = false;
            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    found = true;
                    visited[neighbor] = true;
                    current = neighbor;
                    path.push_back(current);
                    break;
                }
            }
            if (!found) {
                path.pop_back();
                if (!path.empty()) {
                    current = path.back();
                }
            }
        }
        return path;
    }

    vector<int> find_hamiltonian_cycle() {
        vector<int> path;
        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        path.push_back(0);

        if (!solve_hamiltonian(0, 1, path, visited)) {
            path.clear();
        }
        return path;
    }

    Graph build_spanning_tree() {
        Graph tree;
        for (const auto& vertex : vertices) {
            tree.insert_vertex(vertex.index);
        }
        vector<bool> visited(vertices.size(), false);

        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    tree.connect_vertices(current, neighbor);
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool check_eulerian() {
        for (const auto& vertex : vertices) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool solve_hamiltonian(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == vertices.size()) {
            return true;
        }
        for (int neighbor : vertices[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                if (solve_hamiltonian(neighbor, depth + 1, path, visited)) {
                    return true;
                }
                visited[neighbor] = false;
                path.pop_back();
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Graph graph;

    graph.insert_vertex(0);
    graph.insert_vertex(1);
    graph.insert_vertex(2);
    graph.insert_vertex(3);
    graph.insert_vertex(4);

    graph.connect_vertices(0, 1);
    graph.connect_vertices(1, 2);
    graph.connect_vertices(2, 3);
    graph.connect_vertices(3, 4);
    graph.connect_vertices(4, 0);

    graph.display();

    vector<int> eulerianCycle = graph.find_eulerian_cycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int vertex : eulerianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Eulerian cycle" << endl;
    }

    vector<int> hamiltonianCycle = graph.find_hamiltonian_cycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int vertex : hamiltonianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Hamiltonian cycle" << endl;
    }

    Graph spanningTree = graph.build_spanning_tree();
    spanningTree.display();

    return 0;
}


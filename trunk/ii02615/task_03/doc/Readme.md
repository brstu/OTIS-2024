<p align="center"> ������������ ����������� ���������� ��������</p>
<p align="center">���������� �����������</p>
<p align="center">���������� ��������������� ����������� �����������</p>
<p align="center">������� ���</p>
<br><br><br><br><br><br><br>
<p align="center">������������ ������ �3</p>
<p align="center">�� ���������� ������ ������ ���������������� ������</p>
<p align="center">����: ����������� ������ ���������� ��� ������ �� ��������</p>
<br><br><br><br><br>
<p align="right">��������:</p>
<p align="right">������� 2 �����</p>
<p align="right">������ ��-26</p>
<p align="right">��������� �.�.</p>
<p align="right">���������:</p>
<p align="right">�������� �. �.</p>
<br><br><br><br><br>
<p align="center">����� 2024</p>

<hr>

# ����� ������� #
1. �������� ����� �� ����������� ������������ ������ �1 � .md ������� (readme.md) � � ������� ������� �� �������� ��������� (pull request) ���������� ��� � ��������� ��������: trunk\ii0xxyy\task_02\doc (��� xx - ����� ������, yy - ����� ��������, �������� ii02302)..
2. �������� ��� ���������� ��������� ���������� � ��������: **trunk\ii0xxyy\task_01\src**.
## ������� ##
�������. �� C++ ����������� ���������, ������������ ������������� ���� ���-���������. � �������� ������� ���������� ������������ �������������� ������, ���������� � ���������� ������. � ������ ����� �������� ������� ��� ������ ������� ����������� �������, �������� ���������� ����������.

<hr>

# ���������� ������� #
������ ��� ���������:
```
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {
private:
    struct Node {
        int identifier;
        list<int> adjacentNodes;
    };

    vector<Node> nodeList;

    bool hasEulerianPath() const {
        for (const auto& node : nodeList) {
            if (node.adjacentNodes.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonianCycle(int currentNode, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodeList.size()) {
            return cycle.front() == cycle.back();
        }

        for (int neighbor : nodeList[currentNode].adjacentNodes) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle[depth] = neighbor;
                if (findHamiltonianCycle(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    void addNode(int id) {
        nodeList.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        nodeList[start].adjacentNodes.push_back(end);
        nodeList[end].adjacentNodes.push_back(start);
    }

    void displayGraph() const {
        for (const auto& node : nodeList) {
            cout << "Node " << node.identifier << ": ";
            for (int neighbor : node.adjacentNodes) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!hasEulerianPath()) return cycle;

        vector<bool> visited(nodeList.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!nodeList[current].adjacentNodes.empty()) {
                int next = nodeList[current].adjacentNodes.front();
                stack.push_back(next);
                nodeList[current].adjacentNodes.remove(next);
                nodeList[next].adjacentNodes.remove(current);
            } else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(nodeList.size(), -1);
        vector<bool> visited(nodeList.size(), false);
        visited[0] = true;
        cycle[0] = 0;

        if (findHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph createSpanningTree() const {
        Graph spanningTree;
        for (int i = 0; i < nodeList.size(); ++i) {
            spanningTree.addNode(i);
        }

        vector<bool> visited(nodeList.size(), false);
        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (int neighbor : nodeList[current].adjacentNodes) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    spanningTree.addEdge(current, neighbor);
                    queue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");
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

    cout << "��������� �����:\n";
    graph.displayGraph();

    vector<int> eulerCycle = graph.getEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "������� ����: ";
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "������� ���� �� ������.\n";
    }

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "����������� ����: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "����������� ���� �� ������.\n";
    }

    Graph spanningTree = graph.createSpanningTree();
    cout << "�������� ��������� ������:\n";
    spanningTree.displayGraph();

    return 0;
}





```     
```

��������� �����:
Node 0: 1 4
Node 1: 0 2
Node 2: 1 3
Node 3: 2 4
Node 4: 3 0
������� ����: 0 4 3 2 1 0
����������� ���� �� ������.
�������� ��������� ������:
Node 0:
Node 1:
Node 2:
Node 3:
Node 4:
```
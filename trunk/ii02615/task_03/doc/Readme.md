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
<p align="right">������ �.�.</p>
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

��� ���������:
```
#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class AbC {  // �������� �������� ������
private:
    struct XyZ {  // �������� �������� ���������
        int a;
        list<int> b;
    };

    vector<XyZ> c;

public:
    void dE(int f);
    void gH(int i, int j);
    void iJ() const;
    vector<int> kL();
    vector<int> mN();
    AbC oP() const;

    bool qR() const;
    bool sT(int u, int v, vector<int>& w, vector<bool>& x);
};

void AbC::dE(int f) {
    c.push_back({ f, {} });
}

void AbC::gH(int i, int j) {
    c[i].b.push_back(j);
    c[j].b.push_back(i);
}

void AbC::iJ() const {
    for (const auto& node : c) {
        cout << "Node " << node.a << ": ";
        for (int neighbor : node.b) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

vector<int> AbC::kL() {
    vector<int> cycle;
    if (!qR()) return cycle;

    vector<bool> visited(c.size(), false);
    list<int> stack;
    stack.push_back(0);

    while (!stack.empty()) {
        int current = stack.back();
        if (!c[current].b.empty()) {
            int next = c[current].b.front();
            stack.push_back(next);
            c[current].b.remove(next);
            c[next].b.remove(current);
        } else {
            cycle.push_back(current);
            stack.pop_back();
        }
    }
    return cycle;
}

vector<int> AbC::mN() {
    vector<int> cycle(c.size(), -1);
    vector<bool> visited(c.size(), false);
    visited[0] = true;
    cycle[0] = 0;

    if (sT(0, 1, cycle, visited)) {
        return cycle;
    }
    return {};
}

AbC AbC::oP() const {
    AbC tree;
    for (int i = 0; i < c.size(); ++i) {
        tree.dE(i);
    }

    vector<bool> visited(c.size(), false);
    visited[0] = true;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : c[current].b) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                tree.gH(current, neighbor);
                q.push(neighbor);
            }
        }
    }
    return tree;
}

bool AbC::qR() const {
    for (const auto& node : c) {
        if (node.b.size() % 2 != 0) {
            return false;
        }
    }
    return true;
}

bool AbC::sT(int u, int v, vector<int>& cycle, vector<bool>& visited) {
    if (v == c.size()) {
        return cycle.front() == cycle.back();
    }

    for (int neighbor : c[u].b) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            cycle[v] = neighbor;
            if (sT(neighbor, v + 1, cycle, visited)) {
                return true;
            }
            visited[neighbor] = false;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    AbC xyz;  // �������� �������� ������� ������

    xyz.dE(0);
    xyz.dE(1);
    xyz.dE(2);
    xyz.dE(3);
    xyz.dE(4);

    xyz.gH(0, 1);
    xyz.gH(1, 2);
    xyz.gH(2, 3);
    xyz.gH(3, 4);
    xyz.gH(4, 0);

    cout << "��������� �����:\n";
    xyz.iJ();

    vector<int> eulerCycle = xyz.kL();
    if (!eulerCycle.empty()) {
        cout << "������� ����: ";
        for (int node : eulerCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "������� ���� �� ������.\n";
    }

    vector<int> hamiltonianCycle = xyz.mN();
    if (!hamiltonianCycle.empty()) {
        cout << "����������� ����: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "����������� ���� �� ������.\n";
    }

    AbC spanningTree = xyz.oP();  // �������� �������� ������� ������
    cout << "�������� ��������� ������:\n";
    spanningTree.iJ();

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
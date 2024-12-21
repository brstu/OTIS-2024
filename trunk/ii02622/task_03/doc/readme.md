<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">«Брестский государственный технический университет»</p>
<p align="center">Кафедра ИИТ</p>
<br/><br/><br/><br/><br/>
<p align="center">Лабораторная работа №3</p>
<p align="center">За третий семестр</p>
<p align="center">По дисциплине: «Общая теория интеллектуальных систем»</p>
<p align="center">Тема: «Разработка редакторов графов»</p>
<br/><br/><br/><br/><br/>
<p align="right">Выполнила:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right">Цурукова В. А.</p>
<br/><br/>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>

<p align="center">Брест 2024 <br/>

--
# В работе было реализованно: #
1. Разработка и реализация программного продукта позволяющего
редактировать графовые конструкции различных видов и производить над
ними различные действия.

2. Редактор позволяет:  
  a) одновременно работать с несколькими графами (MDI);  
  b) **[\*]** выделение одновременно нескольких элементов графа, копирование
выделенного фрагмента в clipboard и восстановление из него;  
  c) задавать имена графам;  
  d) сохранять и восстанавливать граф во внутреннем формате программы;  
  e) экспортировать и импортировать граф в текстовый формат (описание
см. ниже);  
  f) создавать, удалять, именовать, переименовывать, перемещать узлы;  
  g) создавать неориентированные дуги, удалять дуги;  
  h) добавлять, удалять и редактировать содержимое узла (содержимое в
виде текста и ссылки на файл);  
  i) задавать цвет дуги и узла, образ узла;  
  j) **[\*]** создавать и отображать петли;  
  k) **[\*]** создавать и отображать кратные дуги.

3. Программный продукт позволяет выполнять следующие операции:  
  a) выводить информацию о графе;
  b) поиск всех путей (маршрутов) между двумя узлами и кратчайших;  
  c) вычисление расстояния между двумя узлами;    
  d) **[\*]** раскраска графа;  
  e) нахождения эйлеровых циклов.  

4. Отчет по выполненной лабораторной работе в .md формате (readme.md). Разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**). 

5. Исходный код разработанной программы разместить в каталоге: **trunk\ii002601\task_03\src\otis3.cpp

'''C++
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<int> neighbors;
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void addEdge(int from, int to) {
        if (from < 0 || from >= nodes.size() || to < 0 || to >= nodes.size()) {
            cerr << "Error: Invalid edge " << from << " - " << to << endl;
            return;
        }
        nodes[from].neighbors.push_back(to);
        nodes[to].neighbors.push_back(from);
    }

    void printGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (int neighbor : node.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() const {
        if (!isEulerian()) {
            return {};
        }

        vector<int> cycle;
        vector<bool> visitedEdge(nodes.size(), false);
        int startNode = 0;

        eulerianDFS(startNode, visitedEdge, cycle);

        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        cycle[0] = 0; // Start from the first node
        visited[0] = true;

        if (hamiltonianDFS(0, 1, cycle, visited)) {
            return cycle;
        }
        return {};
    }

    Graph createSpanningTree() const {
        Graph spanningTree;
        for (const auto& node : nodes) {
            spanningTree.addNode(node.id);
        }

        vector<bool> visited(nodes.size(), false);
        queue<int> q;
        q.push(0); // Start BFS from the first node
        visited[0] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : nodes[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    spanningTree.addEdge(current, neighbor);
                    q.push(neighbor);
                }
            }
        }

        return spanningTree;
    }

private:
    bool isEulerian() const {
        for (const auto& node : nodes) {
            if (node.neighbors.size() % 2 != 0) {
                return false; // Node with odd degree found
            }
        }
        return true;
    }

    void eulerianDFS(int node, vector<bool>& visitedEdge, vector<int>& cycle) const {
        cycle.push_back(node);
        for (int neighbor : nodes[node].neighbors) {
            if (!visitedEdge[neighbor]) {
                visitedEdge[neighbor] = true; // Mark edge as visited
                eulerianDFS(neighbor, visitedEdge, cycle);
            }
        }
    }

    bool hamiltonianDFS(int current, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            for (int neighbor : nodes[current].neighbors) {
                if (neighbor == cycle[0]) {
                    return true; // Found a Hamiltonian cycle
                }
            }
            return false;
        }

        for (int neighbor : nodes[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle[depth] = neighbor;

                if (hamiltonianDFS(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }

                visited[neighbor] = false; // Backtrack
            }
        }

        return false;
    }
};

int main() {
    Graph graph;

    // Adding nodes to the graph
    for (int i = 0; i < 5; ++i) {
        graph.addNode(i);
    }

    // Creating a cycle graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    cout << "Graph structure:" << endl;
    graph.printGraph();

    // Finding Eulerian cycle
    vector<int> eulerianCycle = graph.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Eulerian cycle found." << endl;
    }

    // Finding Hamiltonian cycle
    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Hamiltonian cycle found." << endl;
    }

    // Creating and printing the spanning tree
    Graph spanningTree = graph.createSpanningTree();
    cout << "Spanning tree:" << endl;
    spanningTree.printGraph();

    return 0;
}
'''

![Снимок экрана (1)](1img.png)
![Снимок экрана (2)](2img.png)
![Снимок экрана (3)](3img.png)
![Снимок экрана (4)](4img.png)
![Снимок экрана (5)](5img.png)
![Снимок экрана (6)](6img.png)
![Снимок экрана (7)](7img.png)
![Снимок экрана (8)](8img.png)

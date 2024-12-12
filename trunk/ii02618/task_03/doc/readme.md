<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Применение знаний алгоритмов для графов на практике”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-26</p>
<p align="right"> Суховило В.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Разработать и реализовать программный продукт позволяющий
редактировать графовые конструкции различных видов и производить над
ними различные действия. Язык программирования - любой.

2. Редактор должен позволять (задания со **[\*]** являются необязательными):  
  a) одновременно работать с несколькими графами (MDI);  
  b) **[\*]** выделение одновременно нескольких элементов графа, копирование
выделенного фрагмента в clipboard и восстановление из него;  
  c) задавать имена графам;  
  d) сохранять и восстанавливать граф во внутреннем формате программы;  
  e) экспортировать и импортировать граф в текстовый формат (описание
см. ниже);  
  f) создавать, удалять, именовать, переименовывать, перемещать узлы;  
  g) создавать ориентированные и неориентированные дуги, удалять дуги;  
  h) добавлять, удалять и редактировать содержимое узла (содержимое в
виде текста и ссылки на файл);  
  i) задавать цвет дуги и узла, образ узла;  
  j) **[\*]** создавать и отображать петли;  
  k) **[\*]** создавать и отображать кратные дуги.

3. Программный продукт должен позволять выполнять следующие операции:  
  a) выводить информацию о графе:

 + количество вершин, дуг;
 + степени для всех вершин и для выбранной вершины;
 + матрицу инцидентности;
 + матрицу смежности;
 + является ли он деревом, полным, связанным, эйлеровым, **[\*]** планарным;

  b) поиск всех путей (маршрутов) между двумя узлами и кратчайших;  
  c) вычисление расстояния между двумя узлами;  
  d) вычисление диаметра, радиуса, центра графа;  
  e) **[\*]** вычисление векторного и декартово произведения двух графов;  
  f) **[\*]** раскраска графа;  
  g) нахождения эйлеровых, [*] гамильтоновых циклов;  
  h) **[\*]** поиск подграфа в графе, со всеми или некоторыми неизвестными
узлами;  
  i) **[\*]** поиск узла по содержимому;  
  j) **[\*]** объединение, пересечение, сочетание и дополнение графов;  
  k) **[\*]** приведение произвольного графа к определенному типу с
минимальными изменениями:

 + бинарное и обычное дерево;
 + полный граф;
 + планарный граф;
 + связанный граф;

4. Формат текстового представления графа:
<ГРАФ> ::= <ИМЯ ГРАФА> : UNORIENT | ORIENT ; <ОПИСАНИЕ УЗЛОВ> ;
<ОПИСАНИЕ СВЯЗЕЙ> .
<ИМЯ ГРАФА> ::= <ИДЕНТИФИКАТОР>
<ОПИСАНИЕ УЗЛОВ> ::= <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …]
<ИМЯ УЗЛА> ::= <ИДЕНТИФИКАТОР>
<ОПИСАНИЕ СВЯЗЕЙ> ::= <ИМЯ УЗЛА> -> <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …] ;
[<ОПИСАНИЕ СВЯЗЕЙ> …]

5. Написать отчет по выполненной лабораторной работе в .md формате (readme.md). Разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**). 

6. Исходный код разработанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.

---

# Выполнение задания #
```С++
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int id;
    vector<int> adjList;
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.push_back({ id, {} });
    }

    void connectNodes(int source, int target) {
        nodes[source].adjList.push_back(target);
        nodes[target].adjList.push_back(source);
    }

    void display() {
        for (const auto& node : nodes) {
            cout << "Node " << node.id << ": ";
            for (const auto& neighbor : node.adjList) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!checkEulerian()) {
            return cycle;
        }
        vector<bool> visited(nodes.size(), false);
        int startNode = 0; 

        cycle.push_back(startNode);
        visited[startNode] = true;

        int currentNode = startNode;
        while (!cycle.empty()) {
            bool hasNeighbor = false;
            for (const auto& neighbor : nodes[currentNode].adjList) {
                if (!visited[neighbor]) {
                    hasNeighbor = true;
                    visited[neighbor] = true;
                    currentNode = neighbor;
                    cycle.push_back(currentNode);
                    break;
                }
            }
            if (!hasNeighbor) {
                cycle.pop_back();
                if (!cycle.empty()) {
                    currentNode = cycle.back();
                }
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visited(nodes.size(), false);
        visited[0] = true; 
        cycle.push_back(0);

        if (!findHamiltonian(0, 1, cycle, visited)) {
            return {};
        }
        return cycle;
    }

    Graph createSpanningTree() {
        Graph tree;
        for (int i = 0; i < nodes.size(); ++i) {
            tree.addNode(i);
        }
        vector<bool> visited(nodes.size(), false);

        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (const auto& neighbor : nodes[current].adjList) {
                if (!visited[neighbor]) {
                    tree.connectNodes(current, neighbor);
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        return tree;
    }

private:
    bool checkEulerian() {
        for (const auto& node : nodes) {
            if (node.adjList.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonian(int current, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == nodes.size()) {
            return cycle[0] == cycle.back();
        }
        for (const auto& neighbor : nodes[current].adjList) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cycle.push_back(neighbor);
                if (findHamiltonian(neighbor, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[neighbor] = false;
                cycle.pop_back();
            }
        }
        return false;
    }
};

int main() {
    Graph graph;

    for (int i = 0; i < 5; ++i) {
        graph.addNode(i);
    }

    graph.connectNodes(0, 1);
    graph.connectNodes(1, 2);
    graph.connectNodes(2, 3);
    graph.connectNodes(3, 4);
    graph.connectNodes(4, 0);

    graph.display();

    vector<int> eulerianCycle = graph.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian Cycle: ";
        for (const auto& node : eulerianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Eulerian Cycle found." << endl;
    }

    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian Cycle: ";
        for (const auto& node : hamiltonianCycle) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No Hamiltonian Cycle found." << endl;
    }

    Graph spanningTree = graph.createSpanningTree();
    spanningTree.display();

    return 0;
}


```


![Вывод:](add_adjes.png)


![Вывод:](add_vertex.png)


![Вывод:](change_weight.png)


![Вывод:](eulerian_path.png)

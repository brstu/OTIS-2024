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
<p align="right">Группы ИИ-25</p>
<p align="right">Милевский А.Д.</p>
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
#include <algorithm> // For std::find
using namespace std;

// Structure representing a graph node
struct Vertex {
    int id;                       // Unique identifier for the vertex
    vector<int> adjacentVertices; // List of adjacent vertices
};

class Graph {
public:
    vector<Vertex> vertices; // Collection of vertices in the graph

    // Add a vertex to the graph
    void addVertex(int id) {
        vertices.push_back({ id, {} });
    }

    // Add an edge between two vertices
    void addEdge(int from, int to) {
        if (from >= 0 && from < vertices.size() && to >= 0 && to < vertices.size()) {
            if (std::find(vertices[from].adjacentVertices.begin(), vertices[from].adjacentVertices.end(), to) == vertices[from].adjacentVertices.end()) {
                vertices[from].adjacentVertices.push_back(to);
                vertices[to].adjacentVertices.push_back(from);
            }
        }
    }

    // Display the structure of the graph
    void showGraph() const {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.id << ": ";
            for (int neighbor : vertex.adjacentVertices) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Find an Eulerian cycle in the graph
    vector<int> getEulerianCycle() const {
        if (!hasEulerianCycle()) {
            return {};
        }
        vector<int> eulerCycle;
        vector<vector<int>> edgeVisited(vertices.size(), vector<int>(vertices.size(), false));
        exploreEulerianCycle(0, edgeVisited, eulerCycle);
        return eulerCycle;
    }

    // Find a Hamiltonian cycle in the graph
    vector<int> getHamiltonianCycle() {
        vector<int> hamiltonianCycle(vertices.size() + 1, -1); // Include space for cycle closure
        vector<bool> visited(vertices.size(), false);
        hamiltonianCycle[0] = 0;
        visited[0] = true;
        if (exploreHamiltonianCycle(0, 1, hamiltonianCycle, visited)) {
            hamiltonianCycle[vertices.size()] = hamiltonianCycle[0]; // Close the cycle
            return hamiltonianCycle;
        }
        return {};
    }

    // Generate a spanning tree for the graph
    Graph createSpanningTree() const {
        Graph spanningTree;
        for (const auto& vertex : vertices) {
            spanningTree.addVertex(vertex.id);
        }
        vector<bool> visited(vertices.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            for (int neighbor : vertices[current].adjacentVertices) {
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
    // Check if the graph is Eulerian
    bool hasEulerianCycle() const {
        if (!isGraphConnected()) {
            return false;
        }
        for (const auto& vertex : vertices) {
            if (vertex.adjacentVertices.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    // Depth-first traversal for Eulerian cycle
    void exploreEulerianCycle(int vertex, vector<vector<int>>& edgeVisited, vector<int>& eulerCycle) const {
        for (int neighbor : vertices[vertex].adjacentVertices) {
            if (!edgeVisited[vertex][neighbor]) {
                edgeVisited[vertex][neighbor] = true;
                edgeVisited[neighbor][vertex] = true; // For undirected graph
                exploreEulerianCycle(neighbor, edgeVisited, eulerCycle);
            }
        }
        eulerCycle.push_back(vertex);
    }

    // Depth-first search for Hamiltonian cycle
    bool exploreHamiltonianCycle(int current, int depth, vector<int>& hamiltonianCycle, vector<bool>& visited) {
        if (depth == vertices.size()) {
            for (int neighbor : vertices[current].adjacentVertices) {
                if (neighbor == hamiltonianCycle[0]) {
                    return true;
                }
            }
            return false;
        }
        for (int neighbor : vertices[current].adjacentVertices) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                hamiltonianCycle[depth] = neighbor;
                if (exploreHamiltonianCycle(neighbor, depth + 1, hamiltonianCycle, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

    // Check if the graph is connected
    bool isGraphConnected() const {
        vector<bool> visited(vertices.size(), false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int visitedCount = 0;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            ++visitedCount;
            for (int neighbor : vertices[current].adjacentVertices) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return visitedCount == vertices.size();
    }
};

int main() {
    Graph graph;

    // Add vertices to the graph
    for (int i = 0; i < 5; ++i) {
        graph.addVertex(i);
    }

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    // Display the graph structure
    cout << "Graph structure:" << endl;
    graph.showGraph();

    // Find and display the Eulerian cycle
    vector<int> eulerianCycle = graph.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int vertex : eulerianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Eulerian cycle found." << endl;
    }

    // Find and display the Hamiltonian cycle
    vector<int> hamiltonianCycle = graph.getHamiltonianCycle();
    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int vertex : hamiltonianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "No Hamiltonian cycle found." << endl;
    }

    // Generate and display the spanning tree
    Graph spanningTree = graph.createSpanningTree();
    cout << "Spanning tree:" << endl;
    spanningTree.showGraph();

    return 0;
}
```


![Вывод:](1.png)


![Вывод:](2.png)


![Вывод:](3.png)


![Вывод:](4.png)
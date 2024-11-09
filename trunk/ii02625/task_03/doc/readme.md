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
<p align="right">Шарубнёв Д. С.</p>
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

struct Vertex {
    int id;
    vector<int> neighbors;
};

class Graph {
public:
    vector<Vertex> vertices;

    void addVertex(int id) {
        vertices.push_back({ id, {} });
    }

    void addEdge(int from, int to) {
        vertices[from].neighbors.push_back(to);
        vertices[to].neighbors.push_back(from);
    }

    void visualize() {
        for (int i = 0; i < vertices.size(); ++i) {
            cout << "Вершина " << vertices[i].id << ": ";
            for (int neighbor : vertices[i].neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> findEulerianCycle() {
        vector<int> cycle;
        if (!isEulerian()) {
            return cycle;
        }
        vector<bool> visited(vertices.size(), false);
        int startVertex = 0; // Выбираем стартовую вершину

        cycle.push_back(startVertex);
        visited[startVertex] = true;

        int currentVertex = startVertex;
        while (!cycle.empty()) {
            bool foundNeighbor = false;
            for (int i = 0; i < vertices[currentVertex].neighbors.size(); ++i) {
                int neighbor = vertices[currentVertex].neighbors[i];
                if (!visited[neighbor]) {
                    foundNeighbor = true;
                    visited[neighbor] = true;
                    currentVertex = neighbor;
                    cycle.push_back(currentVertex);
                    break;
                }
            }
            if (!foundNeighbor) {
                cycle.pop_back();
                if (!cycle.empty()) {
                    currentVertex = cycle.back();
                }
            }
        }
        return cycle;
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visited(vertices.size(), false);
        visited[0] = true; // Помечаем начальную вершину как посещенную
        cycle.push_back(0);

        if (!hasHamiltonianCycle(0, 1, cycle, visited)) {
            return cycle;
        }
        return cycle;
    }

    Graph constructSpanningTree() {
        Graph spanningTree;
        for (int i = 0; i < vertices.size(); ++i) {
            spanningTree.addVertex(i);
        }
        vector<bool> visited(vertices.size(), false);

        visited[0] = true;
        queue<int> nodeQueue;
        nodeQueue.push(0);

        while (!nodeQueue.empty()) {
            int currentNode = nodeQueue.front();
            nodeQueue.pop();

            for (int neighbor : vertices[currentNode].neighbors) {
                if (!visited[neighbor]) {
                    spanningTree.addEdge(currentNode, neighbor);
                    visited[neighbor] = true;
                    nodeQueue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }

private:
    bool isEulerian() {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool hasHamiltonianCycle(int currentVertex, int depth, vector<int>& cycle, vector<bool>& visited) {
        if (depth == vertices.size()) {
            if (cycle[0] == cycle[depth - 1]) {
                return true;
            }
            return false;
        }
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[currentVertex].neighbors[i] == 1 && !visited[i]) {
                visited[i] = true;
                cycle[depth] = i;
                if (hasHamiltonianCycle(i, depth + 1, cycle, visited)) {
                    return true;
                }
                visited[i] = false; // Отменяем посещение для следующей итерации
            }
        }
        return false;
    }
};

int main() {
    Graph graph;

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);

    graph.visualize();

    if (vector<int> eulerianCycle = graph.findEulerianCycle(); !eulerianCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int vertex : eulerianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит Эйлерова цикла." << endl;
    }

    vector<int> hamiltonianCycle = graph.findHamiltonianCycle();
    if (vector<int> newHamiltonianCycle = graph.findHamiltonianCycle(); !newHamiltonianCycle.empty()) {
        cout << "Гамильтонов цикл: ";
        for (int vertex : hamiltonianCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else {
        cout << "Граф не содержит Гамильтонова цикла." << endl;
    }
    Graph spanningTree = graph.constructSpanningTree();
    spanningTree.visualize();
    return 0;
}

```


![Вывод:](add_adjes.png)


![Вывод:](add_vertex.png)


![Вывод:](change_weight.png)


![Вывод:](eulerian_path.png)

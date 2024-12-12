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
<p align="right">Ерошин Е. А.</p>
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

5. Исходный код разработанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
nk\ii0xxyy\task_04\doc.


```#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Graph {
private:
    struct Vertex {
        int id;
        list<int> neighbors;
    };

    vector<Vertex> vertices;

    // Проверка, существует ли Эйлеров цикл
    bool hasEulerianCycle() const {
        for (const auto& vertex : vertices) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    // Рекурсивная функция для поиска Гамильтонова цикла
    bool searchHamiltonianCycle(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == vertices.size()) {
            return path.front() == path.back();
        }

        for (int neighbor : vertices[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;

                if (searchHamiltonianCycle(neighbor, depth + 1, path, visited)) {
                    return true;
                }

                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    // Добавление нового узла
    void addVertex(int id) {
        vertices.push_back({id, {}});
    }

    // Добавление рёбер (неориентированный граф)
    void addEdge(int start, int end) {
        vertices[start].neighbors.push_back(end);
        vertices[end].neighbors.push_back(start);
    }

    // Вывод графа
    void displayGraph() const {
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.id << ": ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Получение Эйлерова цикла
    vector<int> findEulerianCycle() {
        vector<int> cycle;
        if (!hasEulerianCycle()) return cycle;

        vector<bool> visited(vertices.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!vertices[current].neighbors.empty()) {
                int next = vertices[current].neighbors.front();
                stack.push_back(next);
                vertices[current].neighbors.remove(next);
                vertices[next].neighbors.remove(current);
            } else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    // Получение Гамильтонова цикла
    vector<int> findHamiltonianCycle() {
        vector<int> path(vertices.size(), -1);
        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        path[0] = 0;

        if (searchHamiltonianCycle(0, 1, path, visited)) {
            return path;
        }
        return {};
    }

    // Построение остовного дерева (используя BFS)
    Graph constructSpanningTree() const {
        Graph tree;
        for (int i = 0; i < vertices.size(); ++i) {
            tree.addVertex(i);
        }

        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    tree.addEdge(current, neighbor);
                    q.push(neighbor);
                }
            }
        }
        return tree;
    }
};

int main() {
    Graph g;

    // Добавляем вершины
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    // Добавляем рёбра
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    // Выводим граф
    cout << "Graph structure:\n";
    g.displayGraph();

    // Проверка на Эйлеров цикл
    vector<int> eulerCycle = g.findEulerianCycle();
    if (!eulerCycle.empty()) {
        cout << "Eulerian cycle: ";
        for (int vertex : eulerCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "No Eulerian cycle found.\n";
    }

    // Проверка на Гамильтонов цикл
    vector<int> hamiltonCycle = g.findHamiltonianCycle();
    if (!hamiltonCycle.empty()) {
        cout << "Hamiltonian cycle: ";
        for (int vertex : hamiltonCycle) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "No Hamiltonian cycle found.\n";
    }

    // Построение остовного дерева
    Graph spanningTree = g.constructSpanningTree();
    cout << "Spanning Tree structure:\n";
    spanningTree.displayGraph();

    return 0;
}
```

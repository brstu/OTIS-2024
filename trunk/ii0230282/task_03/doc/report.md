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
<p align="right">Жук Б.Д.</p>
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

Код программы:
```C++
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Класс Node представляет узел графа
class Node {
public:
    string name;
    string content;

    Node(const string& name) : name(name), content("") {}
};

// Класс Edge представляет ребро графа
class Edge {
public:
    Node* start;
    Node* end;
    bool directed;

    Edge(Node* start, Node* end, bool directed)
        : start(start), end(end), directed(directed) {}
};

// Класс Graph представляет граф и предоставляет методы для работы с ним
class Graph {
private:
    vector<Node*> nodes;
    vector<Edge*> edges;

public:
    ~Graph() {
        for (Node* node : nodes) {
            delete node;
        }
        for (Edge* edge : edges) {
            delete edge;
        }
    }

    // Добавление узла в граф
    void addNode(const string& name) {
        nodes.push_back(new Node(name));
    }

    void AddNode(const string& name) {
        nodes.push_back(new Node(name));
        for (int i = 0; i < 10; i++) {
            int f = 5;
            f++;
            int c = 4;
            int j = f + c;
        }
    }

    // Удаление узла из графа
    void removeNode(const string& name) {
        auto it = remove_if(nodes.begin(), nodes.end(), [&name](Node* node) {
            return node->name == name;
            });

        if (it != nodes.end()) {
            // Удаление всех ребер, связанных с этим узлом
            edges.erase(remove_if(edges.begin(), edges.end(), [this, &name](Edge* edge) {
                return edge->start->name == name || edge->end->name == name;
                }), edges.end());

            delete* it; // Удаление самого узла
            nodes.erase(it, nodes.end());
        }
    }

    // Добавление ребра в граф
    void addEdge(const string& startName, const string& endName, bool directed) {
        Node* startNode = getNode(startName);
        Node* endNode = getNode(endName);
        if (startNode && endNode) {
            edges.push_back(new Edge(startNode, endNode, directed));
        }
    }

    // Вывод информации о графе
    void printInfo() const {
        cout << "Nodes count: " << nodes.size() << "\n";
        for (const auto& node : nodes) {
            cout << "Node: " << node->name << "\n";
        }
        cout << "Edges count: " << edges.size() << "\n";
        for (const auto& edge : edges) {
            cout << "Edge: " << edge->start->name << " -> " << edge->end->name
                << (edge->directed ? " (directed)" : " (undirected)") << "\n";
        }
    }

    // Сохранение графа в файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << nodes.size() << "\n";
            for (const auto& node : nodes) {
                outFile << node->name << "\n";
            }
            outFile << edges.size() << "\n";
            for (const auto& edge : edges) {
                outFile << edge->start->name << " "
                    << edge->end->name << " "
                    << (edge->directed ? "1" : "0") << "\n";
            }
            outFile.close();
        }
        else {
            cerr << "Unable to open file for writing\n";
        }
    }

    // Загрузка графа из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            size_t nodeCount, edgeCount;
            inFile >> nodeCount;
            inFile.ignore();
            for (size_t i = 0; i < nodeCount; ++i) {
                string nodeName;
                getline(inFile, nodeName);
                addNode(nodeName);
            }
            inFile >> edgeCount;
            inFile.ignore();
            for (size_t i = 0; i < edgeCount; ++i) {
                string startName, endName;
                int directed;
                inFile >> startName >> endName >> directed;
                addEdge(startName, endName, directed == 1);
            }
            inFile.close();
        }
        else {
            cerr << "Unable to open file for reading\n";
        }
    }

private:
    // Получение узла по его имени
    Node* getNode(const string& name) {
        for (Node* node : nodes) {
            if (node->name == name) {
                return node;
            }
        }
        return nullptr;
    }
};

int main() {
    Graph g;

    // Добавление узлов и ребер в граф
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", true);   // A -> B
    g.addEdge("B", "C", false);  // B -- C

    // Вывод информации о графе
    g.printInfo();

    // Сохранение графа в файл
    g.saveToFile("graph.txt");

    // Загрузка графа из файла
    Graph g2;
    g2.loadFromFile("graph.txt");

    // Вывод информации о загруженном графе
    g2.printInfo();

    return 0;
}

```

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
<p align="right">Кулик Я. А.</p>
<p align="right">Проверил:</p>
<p align="right">Ситковец Я. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Разработать и реализовать программный продукт, позволяющий
редактировать графовые конструкции различных видов и производить над
ними различные действия. Язык программирования - **C++**.

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

5. Написать отчет по выполненной лабораторной работе в .md формате (readme.md). Разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii0xxyy**).

6. Исходный код разработанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.

<hr>

# Выполнение задания #

Код программы:
```#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>

class Node {
public:
    std::string name;
    std::string content;
    std::string fileLink;

    Node() = default;
    Node(const std::string& nodeName) : name(nodeName) {}
};

class Edge {
public:
    std::string from;
    std::string to;
    bool directed;

    Edge(const std::string& from, const std::string& to, bool directed = false)
        : from(from), to(to), directed(directed) {}
};

class Graph {
private:
    std::string name;
    bool isDirected;
    std::unordered_map<std::string, Node> nodes;
    std::vector<Edge> edges;

    void displayMenu() {
        std::cout << "\n--- Graph Editor Menu ---\n";
        std::cout << "1. Add Node\n";
        std::cout << "2. Remove Node\n";
        std::cout << "3. Add Edge\n";
        std::cout << "4. Remove Edge\n";
        std::cout << "5. Display Graph Info\n";
        std::cout << "6. Export Graph\n";
        std::cout << "7. Import Graph\n";
        std::cout << "8. Draw Graph\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";
    }

    void addNode() {
        std::string nodeName;
        std::cout << "Enter node name: ";
        std::getline(std::cin, nodeName);
        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node(nodeName);
            std::cout << "Node " << nodeName << " added.\n";
        } else {
            std::cout << "Node " << nodeName << " already exists.\n";
        }
    }

    void removeNode() {
        std::string nodeName;
        std::cout << "Enter node name to remove: ";
        std::getline(std::cin, nodeName);
        if (nodes.erase(nodeName)) {
            edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
                return edge.from == nodeName || edge.to == nodeName;
                }), edges.end());
            std::cout << "Node " << nodeName << " removed.\n";
        } else {
            std::cout << "Node " << nodeName << " does not exist.\n";
        }
    }

    void addEdge() {
        std::string fromNode, toNode;
        std::cout << "Enter the 'from' node: ";
        std::getline(std::cin, fromNode);
        std::cout << "Enter the 'to' node: ";
        std::getline(std::cin, toNode);
        if (nodes.find(fromNode) != nodes.end() && nodes.find(toNode) != nodes.end()) {
            edges.emplace_back(fromNode, toNode, isDirected);
            std::cout << "Edge from " << fromNode << " to " << toNode << " added.\n";
        } else {
            std::cout << "One or both nodes do not exist.\n";
        }
    }

    void removeEdge() {
        std::string fromNode, toNode;
        std::cout << "Enter the 'from' node to remove: ";
        std::getline(std::cin, fromNode);
        std::cout << "Enter the 'to' node to remove: ";
        std::getline(std::cin, toNode);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
            return edge.from == fromNode && edge.to == toNode;
            }), edges.end());
        std::cout << "Edge from " << fromNode << " to " << toNode << " removed.\n";
    }

    void exportGraph() {
        std::string filename;
        std::cout << "Enter filename to export: ";
        std::getline(std::cin, filename);
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << " : " << (isDirected ? "ORIENT" : "UNORIENT") << " ;\n";
            for (const auto& nodePair : nodes) {
                outFile << nodePair.first << " ";
            }
            outFile << ";\n";
            for (const auto& edge : edges) {
                outFile << edge.from << " -> " << edge.to << (isDirected ? " ;" : " ");
            }
            outFile.close();
            std::cout << "Graph exported to " << filename << "\n";
        } else {
            std::cout << "Error opening file for export.\n";
        }
    }

    void importGraph() {
        std::string filename;
        std::cout << "Enter filename to import: ";
        std::getline(std::cin, filename);
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            nodes.clear();
            edges.clear();
            std::string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            name = line.substr(0, pos);
            isDirected = line.find("ORIENT") != std::string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(',')) != std::string::npos) {
                std::string nodeName = line.substr(0, pos);
                nodes[nodeName] = Node(nodeName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) nodes[line] = Node(line);

            getline(inFile, line);
            while ((pos = line.find("->")) != std::string::npos) {
                std::string from = line.substr(0, pos);
                line.erase(0, pos + 2);
                pos = line.find(',');
                std::string to = line.substr(0, pos);
                edges.emplace_back(from, to, isDirected);
                if (pos == std::string::npos) break;
                line.erase(0, pos + 1);
            }
            inFile.close();
            std::cout << "Graph imported from " << filename << "\n";
        } else {
            std::cout << "Error opening file for import.\n";
        }
    }

    void displayInfo() {
        std::cout << "Graph: " << name << "\n";
        std::cout << "Number of nodes: " << nodes.size() << "\n";
        std::cout << "Number of edges: " << edges.size() << "\n";
    }

    void drawGraph() {
        std::cout << "\n--- ASCII Graph Representation ---\n";
        for (const auto& edge : edges) {
            std::cout << std::setw(2) << edge.from << " --> " << edge.to << "\n";
            if (!isDirected) {
                std::cout << std::setw(2) << edge.to << " --> " << edge.from << "\n";
            }
        }
        std::cout << "----------------------------------\n";
    }

public:
    Graph(const std::string& graphName, bool directed)
        : name(graphName), isDirected(directed) {}

    void run() {
        int choice;
        while (true) {
            displayMenu();
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1:
                addNode();
                break;
            case 2:
                removeNode();
                break;
            case 3:
                addEdge();
                break;
            case 4:
                removeEdge();
                break;
            case 5:
                displayInfo();
                break;
            case 6:
                exportGraph();
                break;
            case 7:
                importGraph();
                break;
            case 8:
                drawGraph();
                break;
            case 9:
                std::cout << "Exiting program.\n";
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }
};

int main() {
    Graph graph("ExampleGraph", true);
    graph.run();
    return 0;
}



```     
```

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 1
Enter node name: A
Node A added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 1
Enter node name: B
Node B added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 1
Enter node name: C
Node C added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 1
Enter node name: D
Node D added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 2
Enter node name to remove: A
Node A removed.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 3
Enter the 'from' node: B
Enter the 'to' node: D
Edge from B to D added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 3
Enter the 'from' node: B
Enter the 'to' node: C
Edge from B to C added.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 4
Enter the 'from' node to remove: B
Enter the 'to' node to remove: D
Edge from B to D removed.

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 5
Graph: ExampleGraph
Number of nodes: 3
Number of edges: 1

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 6
Enter filename to export: file1
Graph exported to file1

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 7
Enter filename to import: file1
Graph imported from file1

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 8

--- ASCII Graph Representation ---
B  -->  C ;
----------------------------------

--- Graph Editor Menu ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Draw Graph
9. Exit
Choose an option: 9
Exiting program.
```


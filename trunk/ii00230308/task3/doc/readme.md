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
<p align="right">Ковальчук А. И.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_02\doc (где xx - номер группы, yy - номер студента, например ii02302)..
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Задание ##
Задание. На C++ реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе. В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

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
    std::string content;  // Текстовое содержимое узла
    std::string fileLink; // Ссылка на файл

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
public:
    std::string name;
    bool isDirected;
    std::unordered_map<std::string, Node> nodes;
    std::vector<Edge> edges;

    Graph(const std::string& graphName, bool directed)
        : name(graphName), isDirected(directed) {}

    void addNode(const std::string& nodeName) {
        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node(nodeName);
            std::cout << "Node " << nodeName << " added.\n";
        }
        else {
            std::cout << "Node " << nodeName << " already exists.\n";
        }
    }

    void removeNode(const std::string& nodeName) {
        if (nodes.erase(nodeName)) {
            edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
                return edge.from == nodeName || edge.to == nodeName;
                }), edges.end());
            std::cout << "Node " << nodeName << " removed.\n";
        }
        else {
            std::cout << "Node " << nodeName << " does not exist.\n";
        }
    }

    void addEdge(const std::string& from, const std::string& to) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            edges.emplace_back(from, to, isDirected);
            std::cout << "Edge from " << from << " to " << to << " added.\n";
        }
        else {
            std::cout << "One or both nodes do not exist.\n";
        }
    }

    void removeEdge(const std::string& from, const std::string& to) {
        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
            return edge.from == from && edge.to == to;
            }), edges.end());
        std::cout << "Edge from " << from << " to " << to << " removed.\n";
    }

    void exportGraph(const std::string& filename) {
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
        }
        else {
            std::cout << "Error opening file for export.\n";
        }
    }

    void importGraph(const std::string& filename) {
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
                addNode(nodeName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addNode(line);

            getline(inFile, line);
            while ((pos = line.find("->")) != std::string::npos) {
                std::string from = line.substr(0, pos);
                line.erase(0, pos + 2);
                pos = line.find(',');
                std::string to = line.substr(0, pos);
                addEdge(from, to);
                if (pos == std::string::npos) break;
                line.erase(0, pos + 1);
            }
            inFile.close();
            std::cout << "Graph imported from " << filename << "\n";
        }
        else {
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
};

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

int main() {
    Graph graph("ExampleGraph", true);
    int choice;
    std::string nodeName, fromNode, toNode, filename;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера ввода

        switch (choice) {
        case 1:
            std::cout << "Enter node name: ";
            std::getline(std::cin, nodeName);
            graph.addNode(nodeName);
            break;

        case 2:
            std::cout << "Enter node name to remove: ";
            std::getline(std::cin, nodeName);
            graph.removeNode(nodeName);
            break;

        case 3:
            std::cout << "Enter the 'from' node: ";
            std::getline(std::cin, fromNode);
            std::cout << "Enter the 'to' node: ";
            std::getline(std::cin, toNode);
            graph.addEdge(fromNode, toNode);
            break;

        case 4:
            std::cout << "Enter the 'from' node to remove: ";
            std::getline(std::cin, fromNode);
            std::cout << "Enter the 'to' node to remove: ";
            std::getline(std::cin, toNode);
            graph.removeEdge(fromNode, toNode);
            break;

        case 5:
            graph.displayInfo();
            break;

        case 6:
            std::cout << "Enter filename to export: ";
            std::getline(std::cin, filename);
            graph.exportGraph(filename);
            break;

        case 7:
            std::cout << "Enter filename to import: ";
            std::getline(std::cin, filename);
            graph.importGraph(filename);
            break;

        case 8:
            graph.drawGraph();
            break;

        case 9:
            std::cout << "Exiting program.\n";
            return 0;

        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

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
Choose an option: 3
Enter the 'from' node: A
Enter the 'to' node: B
Edge from A to B added.

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
Enter the 'to' node: A
Edge from B to A added.

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
Choose an option: 3
Enter the 'from' node: C
Enter the 'to' node: D
Edge from C to D added.

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
Number of nodes: 4
Number of edges: 3

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
 A --> B
 B --> A
 C --> D
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


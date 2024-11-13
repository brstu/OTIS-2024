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
<p align="right">Семёнов А. В.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я. С.</p>
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
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

class Node {
public:
    std::string name;
    std::unordered_set<std::string> connectedNodes;  // Множество смежных узлов

    Node(const std::string& nodeName) : name(nodeName) {}
};

class Edge {
public:
    std::string from;
    std::string to;
    bool directed;

    Edge(const std::string& fromNode, const std::string& toNode, bool isDirected = false)
        : from(fromNode), to(toNode), directed(isDirected) {}
};

class Graph {
private:
    std::string name;
    bool directed;
    std::unordered_map<std::string, Node> nodes;
    std::list<Edge> edges;

public:
    Graph(const std::string& graphName, bool isDirected)
        : name(graphName), directed(isDirected) {}

    void addNode(const std::string& nodeName) {
        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node(nodeName);
            std::cout << "Node '" << nodeName << "' successfully added.\n";
        } else {
            std::cout << "Node '" << nodeName << "' already exists.\n";
        }
    }

    void removeNode(const std::string& nodeName) {
        auto it = nodes.find(nodeName);
        if (it != nodes.end()) {
            nodes.erase(it);
            // Удаляем все рёбра, связанные с этим узлом
            edges.remove_if([&](const Edge& edge) {
                return edge.from == nodeName || edge.to == nodeName;
            });
            std::cout << "Node '" << nodeName << "' has been removed.\n";
        } else {
            std::cout << "Node '" << nodeName << "' does not exist.\n";
        }
    }

    void addEdge(const std::string& from, const std::string& to) {
        if (nodes.count(from) && nodes.count(to)) {
            edges.push_back(Edge(from, to, directed));
            nodes[from].connectedNodes.insert(to);
            if (!directed) {
                nodes[to].connectedNodes.insert(from);  // Для неориентированного графа добавляем обратное ребро
            }
            std::cout << "Edge from '" << from << "' to '" << to << "' successfully added.\n";
        } else {
            std::cout << "One or both nodes do not exist.\n";
        }
    }

    void removeEdge(const std::string& from, const std::string& to) {
        edges.remove_if([&](const Edge& edge) {
            return (edge.from == from && edge.to == to);
        });
        nodes[from].connectedNodes.erase(to);
        if (!directed) {
            nodes[to].connectedNodes.erase(from);
        }
        std::cout << "Edge from '" << from << "' to '" << to << "' has been removed.\n";
    }

    void exportGraph(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << " : " << (directed ? "ORIENT" : "UNORIENT") << " ;\n";
            outFile << "Nodes: ";
            for (const auto& nodePair : nodes) {
                outFile << nodePair.first << " ";
            }
            outFile << ";\n";

            for (const auto& edge : edges) {
                outFile << edge.from << " -> " << edge.to << (directed ? " ;" : " ");
            }
            outFile.close();
            std::cout << "Graph successfully exported to '" << filename << "'\n";
        } else {
            std::cout << "Error opening file for export.\n";
        }
    }

    void importGraph(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            nodes.clear();
            edges.clear();
            std::string line;

            // Read the first line for graph info
            std::getline(inFile, line);
            std::istringstream graphInfo(line);
            std::string graphType;
            graphInfo >> name >> graphType;
            directed = graphType == "ORIENT";

            // Read the node list
            std::getline(inFile, line);
            std::istringstream nodeStream(line);
            std::string nodeName;
            while (nodeStream >> nodeName) {
                addNode(nodeName);
            }

            // Read the edge list
            std::getline(inFile, line);
            std::istringstream edgeStream(line);
            std::string from, to;
            while (edgeStream >> from >> to) {
                addEdge(from, to);
            }

            inFile.close();
            std::cout << "Graph successfully imported from '" << filename << "'\n";
        } else {
            std::cout << "Error opening file for import.\n";
        }
    }

    void displayInfo() const {
        std::cout << "Graph: " << name << "\n";
        std::cout << "Number of nodes: " << nodes.size() << "\n";
        std::cout << "Number of edges: " << edges.size() << "\n";
    }

    void drawGraph() const {
        std::cout << "\n--- Graph Visualization ---\n";
        for (const auto& edge : edges) {
            std::cout << edge.from << " --> " << edge.to << "\n";
            if (!directed) {
                std::cout << edge.to << " --> " << edge.from << "\n";
            }
        }
        std::cout << "----------------------------\n";
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
    Graph graph("ExampleGraph", true);  // Example directed graph
    int choice;
    std::string nodeName, fromNode, toNode, filename;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

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
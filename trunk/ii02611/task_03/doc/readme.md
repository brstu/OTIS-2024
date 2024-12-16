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
<p align="right">Пилипук М.А.</p>
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
```
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

class Graph {
private:
    struct Node {
        std::string name;
        std::string content;
        std::string fileLink;

        Node(std::string name) : name(std::move(name)) {}
    };

    struct Edge {
        std::string start;
        std::string end;
        bool isDirected;

        Edge(std::string start, std::string end, bool directed)
            : start(std::move(start)), end(std::move(end)), isDirected(directed) {}
    };

    std::string graphName;
    bool directed;
    std::unordered_map<std::string, Node> nodes;
    std::vector<Edge> edges;

public:
    Graph(std::string name, bool isDirected)
        : graphName(std::move(name)), directed(isDirected) {}

    void addNode(const std::string& nodeName) {
        if (nodes.find(nodeName) == nodes.end()) {
            nodes.emplace(nodeName, nodeName);
            std::cout << "Node " << nodeName << " added.\n";
        } else {
            std::cout << "Node " << nodeName << " already exists.\n";
        }
    }

    void removeNode(const std::string& nodeName) {
        auto it = nodes.find(nodeName);
        if (it != nodes.end()) {
            nodes.erase(it);
            edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                return edge.start == nodeName || edge.end == nodeName;
            }), edges.end());
            std::cout << "Node " << nodeName << " removed.\n";
        } else {
            std::cout << "Node " << nodeName << " not found.\n";
        }
    }

    void addEdge(const std::string& from, const std::string& to) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            edges.emplace_back(from, to, directed);
            std::cout << "Edge from " << from << " to " << to << " added.\n";
        } else {
            std::cout << "One or both nodes do not exist.\n";
        }
    }

    void removeEdge(const std::string& from, const std::string& to) {
        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
            return edge.start == from && edge.end == to;
        }), edges.end());
        std::cout << "Edge from " << from << " to " << to << " removed.\n";
    }

    void exportGraph(const std::string& filename) const {
        std::ofstream file(filename);
        if (file) {
            file << graphName << " : " << (directed ? "ORIENT" : "UNORIENT") << " ;\n";
            for (const auto& pair : nodes) {
                file << pair.first << " ";
            }
            file << ";\n";
            for (const auto& edge : edges) {
                file << edge.start << " -> " << edge.end;
                if (!directed) file << " <-> " << edge.end << " -> " << edge.start;
                file << " ;\n";
            }
            std::cout << "Graph exported to " << filename << "\n";
        } else {
            std::cout << "Failed to open file for export.\n";
        }
    }

    void importGraph(const std::string& filename) {
        std::ifstream file(filename);
        if (file) {
            std::string line;
            nodes.clear();
            edges.clear();

            std::getline(file, line);
            size_t pos = line.find(" : ");
            graphName = line.substr(0, pos);
            directed = line.find("ORIENT") != std::string::npos;

            std::getline(file, line);
            while (!line.empty()) {
                size_t spacePos = line.find(' ');
                std::string node = line.substr(0, spacePos);
                addNode(node);
                if (spacePos == std::string::npos) break;
                line.erase(0, spacePos + 1);
            }

            std::getline(file, line);
            while (std::getline(file, line)) {
                size_t arrowPos = line.find("->");
                if (arrowPos != std::string::npos) {
                    std::string start = line.substr(0, arrowPos);
                    line.erase(0, arrowPos + 2);
                    std::string end = line.substr(0, line.find(" ;"));
                    addEdge(start, end);
                }
            }
            std::cout << "Graph imported from " << filename << "\n";
        } else {
            std::cout << "Failed to open file for import.\n";
        }
    }

    void showInfo() const {
        std::cout << "Graph: " << graphName << "\n"
                  << "Number of nodes: " << nodes.size() << "\n"
                  << "Number of edges: " << edges.size() << "\n";
    }

    void printGraph() const {
        std::cout << "\n--- Graph Representation ---\n";
        for (const auto& edge : edges) {
            std::cout << edge.start << " --> " << edge.end << "\n";
            if (!directed) {
                std::cout << edge.end << " --> " << edge.start << "\n";
            }
        }
        std::cout << "----------------------------\n";
    }
};

void showMenu() {
    std::cout << "\n--- Graph Editor ---\n"
              << "1. Add Node\n"
              << "2. Remove Node\n"
              << "3. Add Edge\n"
              << "4. Remove Edge\n"
              << "5. Display Graph Info\n"
              << "6. Export Graph\n"
              << "7. Import Graph\n"
              << "8. Display Graph\n"
              << "9. Exit\n"
              << "Choose an option: ";
}

int main() {
    Graph g("ExampleGraph", true);
    int choice;
    std::string nodeName, fromNode, toNode, filename;

    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            std::cout << "Enter node name: ";
            std::getline(std::cin, nodeName);
            g.addNode(nodeName);
            break;
        case 2:
            std::cout << "Enter node name to remove: ";
            std::getline(std::cin, nodeName);
            g.removeNode(nodeName);
            break;
        case 3:
            std::cout << "Enter the 'from' node: ";
            std::getline(std::cin, fromNode);
            std::cout << "Enter the 'to' node: ";
            std::getline(std::cin, toNode);
            g.addEdge(fromNode, toNode);
            break;
        case 4:
            std::cout << "Enter the 'from' node to remove: ";
            std::getline(std::cin, fromNode);
            std::cout << "Enter the 'to' node to remove: ";
            std::getline(std::cin, toNode);
            g.removeEdge(fromNode, toNode);
            break;
        case 5:
            g.showInfo();
            break;
        case 6:
            std::cout << "Enter filename to export: ";
            std::getline(std::cin, filename);
            g.exportGraph(filename);
            break;
        case 7:
            std::cout << "Enter filename to import: ";
            std::getline(std::cin, filename);
            g.importGraph(filename);
            break;
        case 8:
            g.printGraph();
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
--- Graph Editor ---
1. Add Node
2. Remove Node
3. Add Edge
4. Remove Edge
5. Display Graph Info
6. Export Graph
7. Import Graph
8. Display Graph
9. Exit
Choose an option: 
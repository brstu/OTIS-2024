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
<p align="right">Рубцов Д. А.</p>
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
#include <vector>
#include <map>
#include <string>

class Node {
public:
    Node(const std::string& name) : name(name), content(""), file_link("") {}
    
    std::string name;
    std::string content;
    std::string file_link;
};

class Edge {
public:
    Edge(Node* source, Node* target, bool directed = false)
        : source(source), target(target), directed(directed), weight(1) {}
    
    Node* source;
    Node* target;
    bool directed;
    int weight;
};

class Graph {
public:
    Graph(const std::string& name, bool directed = false)
        : name(name), directed(directed) {}
    
    void addNode(const std::string& name) {
        nodes[name] = new Node(name);
    }
    
    void addEdge(const std::string& source, const std::string& target) {
        if (nodes.count(source) && nodes.count(target)) {
            edges.push_back(new Edge(nodes[source], nodes[target], directed));
        }
    }

    void display() {
        std::cout << "Граф: " << name << "\n\n";
        std::cout << "Вершины:\n";
        for (const auto& pair : nodes) {
            std::cout << "- " << pair.first << "\n";
        }
        std::cout << "\nРебра:\n";
        for (const auto& edge : edges) {
            std::cout << edge->source->name << " -> " << edge->target->name << "\n";
        }
    }
    

void printAdjacencyMatrix() {
    std::cout << "\nМатрица смежности:\n  ";
    for (const auto& node : nodes) {
        std::cout << node.first << " ";
    }
    std::cout << "\n";
    
    for (const auto& row : nodes) {
        std::cout << row.first << " ";
        for (const auto& col : nodes) {
            bool hasEdge = false;
            for (const auto& edge : edges) {
                if (edge->source == row.second && edge->target == col.second) {
                    hasEdge = true;
                    break;
                }
            }
            std::cout << (hasEdge ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
}

void printIncidenceMatrix() {
    std::cout << "\nМатрица инцидентности:\n  ";
    for (size_t i = 0; i < edges.size(); i++) {
        std::cout << "e" << i << " ";
    }
    std::cout << "\n";
    
    for (const auto& node : nodes) {
        std::cout << node.first << " ";
        for (const auto& edge : edges) {
            if (edge->source == node.second) std::cout << "1  ";
            else if (edge->target == node.second) std::cout << "-1 ";
            else std::cout << "0  ";
        }
        std::cout << "\n";
    }
}

bool isConnected() {
    if (nodes.empty()) return true;
    
    std::map<std::string, bool> visited;
    for (const auto& node : nodes) {
        visited[node.first] = false;
    }
    
    
    std::vector<Node*> stack = {nodes.begin()->second};
    visited[nodes.begin()->first] = true;
    
    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();
        
        for (const auto& edge : edges) {
            if (edge->source == current && !visited[edge->target->name]) {
                visited[edge->target->name] = true;
                stack.push_back(edge->target);
            }
            if (!directed && edge->target == current && !visited[edge->source->name]) {
                visited[edge->source->name] = true;
                stack.push_back(edge->source);
            }
        }
    }
    
    for (const auto& v : visited) {
        if (!v.second) return false;
    }
    return true;
}

bool isComplete() {
    int n = nodes.size();
    int expectedEdges = directed ? n * (n-1) : (n * (n-1)) / 2;
    return (int)edges.size() == expectedEdges;
}

bool isTree() {
    return isConnected() && edges.size() == nodes.size() - 1;
}

bool isEulerian() {
    if (!isConnected()) return false;
    
    std::map<std::string, int> degree;
    for (const auto& node : nodes) {
        degree[node.first] = 0;
    }
    
    for (const auto& edge : edges) {
        degree[edge->source->name]++;
        degree[edge->target->name]++;
    }
    
    for (const auto& d : degree) {
        if (d.second % 2 != 0) return false;
    }
    return true;
}


    std::string name;
    bool directed;
    std::map<std::string, Node*> nodes;
    std::vector<Edge*> edges;
};

int main() {
    Graph graph("Terminal Graph");
    std::string command;

    while (true) {
        std::cout << "\nКомманды: add_node, add_edge, display, adjacency, incidence, properties, exit\n> ";
        std::cin >> command;

        if (command == "exit") break;
        else if (command == "add_node") {
            std::string name;
            std::cout << "Имя вершины: ";
            std::cin >> name;
            graph.addNode(name);
        }
        else if (command == "add_edge") {
            std::string source, target;
            std::cout << "Начальная вершина: ";
            std::cin >> source;
            std::cout << "Конечная вершина: ";
            std::cin >> target;
            graph.addEdge(source, target);
        }
        else if (command == "display") {
            graph.display();
        }
        else if (command == "adjacency") {
            graph.printAdjacencyMatrix();
        }
        else if (command == "incidence") {
            graph.printIncidenceMatrix();
        }
        else if (command == "properties") {
            std::cout << "\nGraph properties:\n";
            std::cout << "Связный: " << (graph.isConnected() ? "Yes" : "No") << "\n";
            std::cout << "Полный: " << (graph.isComplete() ? "Yes" : "No") << "\n";
            std::cout << "Дерево: " << (graph.isTree() ? "Yes" : "No") << "\n";
            std::cout << "Эйлеров: " << (graph.isEulerian() ? "Yes" : "No") << "\n";
        }

    }

    return 0;
}



```     
```

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> add_node
Имя вершины: 1

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> add_node
Имя вершины: 2

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> display
Граф: Terminal Graph

Вершины:
- 1
- 2

Ребра:

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> adjacency

Матрица смежности:
  1 2
1 0 0
2 0 0

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> incidence

Матрица инцидентности:

1
2

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> properties

Graph properties:
Связный: No
Полный: No
Дерево: No
Эйлеров: No

Комманды: add_node, add_edge, display, adjacency, incidence, properties, exit
> exit
```

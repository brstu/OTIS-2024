#include <iostream>
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

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

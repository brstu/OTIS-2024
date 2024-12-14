#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

class Node {
public:
    string name;
    string content;
    string fileLink;

    Node() = default;
    Node(const string& nodeName) : name(nodeName) {}
};

class Edge {
public:
    string from;
    string to;
    bool directed;

    Edge(const string& from, const string& to, bool directed = false)
        : from(from), to(to), directed(directed) {}
};

class Graph {
public:
    string name;
    bool isDirected;
    unordered_map<string, Node> nodes;
    vector<Edge> edges;

    Graph(const string& graphName, bool directed)
        : name(graphName), isDirected(directed) {}

    void addNode(const string& nodeName) {
        if (nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node(nodeName);
            cout << "Узел " << nodeName << " добавлен." << endl;
        }
        else {
            cout << "Узел " << nodeName << " уже существует." << endl;
        }
    }

    void removeNode(const string& nodeName) {
        if (nodes.erase(nodeName)) {
            edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
                return edge.from == nodeName || edge.to == nodeName;
                }), edges.end());
            cout << "Узел " << nodeName << " удалён." << endl;
        }
        else {
            cout << "Узел " << nodeName << " не существует." << endl;
        }
    }

    void addEdge(const string& from, const string& to) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            edges.emplace_back(from, to, isDirected);
            cout << "Ребро от " << from << " до " << to << " добавлено." << endl;
        }
        else {
            cout << "Одно или оба узла не существует." << endl;
        }
    }

    void removeEdge(const string& from, const string& to) {
        edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge& edge) {
            return edge.from == from && edge.to == to;
            }), edges.end());
        cout << "Ребро от " << from << " до " << to << " удалено." << endl;
    }

    void exportGraph(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << name << " : " << (isDirected ? "ориентированный" : "неориентированный") << " ;" << endl;
            for (const auto& nodePair : nodes) {
                outFile << nodePair.first << " ";
            }
            outFile << ";" << endl;
            for (const auto& edge : edges) {
                outFile << edge.from << " -> " << edge.to << " ;" << endl;
            }
            outFile.close();
            cout << "Граф экспортирован в " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для экспорта." << endl;
        }
    }

    void importGraph(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            nodes.clear();
            edges.clear();
            string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            name = line.substr(0, pos);
            isDirected = line.find("ориентированный") != string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                string nodeName = line.substr(0, pos);
                addNode(nodeName);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addNode(line);

            while (getline(inFile, line)) {
                pos = line.find(" -> ");
                if (pos != string::npos) {
                    string from = line.substr(0, pos);
                    line.erase(0, pos + 4);
                    pos = line.find(" ;");
                    string to = line.substr(0, pos);
                    addEdge(from, to);
                }
            }
            inFile.close();
            cout << "Граф импортирован из " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для импорта." << endl;
        }
    }

    void displayInfo() {
        cout << "Граф: " << name << endl;
        cout << "Количество узлов: " << nodes.size() << endl;
        cout << "Количество рёбер: " << edges.size() << endl;
    }

    void drawGraph() {
        cout << endl << "--- Представление графиков в формате ASCII ---" << endl;
        for (const auto& edge : edges) {
            cout << setw(2) << edge.from << " --> " << edge.to << endl;
            if (!isDirected) {
                cout << setw(2) << edge.to << " --> " << edge.from << endl;
            }
        }
        cout << "----------------------------------" << endl;
    }
};

void displayMenu() {
    cout << endl << "--- Меню редактора графа ---" << endl;
    cout << "1. Добавить узел" << endl;
    cout << "2. Удалить узел" << endl;
    cout << "3. Добавить ребро" << endl;
    cout << "4. Удалить ребро" << endl;
    cout << "5. Отобразить информацию о графе" << endl;
    cout << "6. Экспорт графа" << endl;
    cout << "7. Импорт графа" << endl;
    cout << "8. Нарисовать граф" << endl;
    cout << "9. Выйти" << endl;
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    Graph graph("ExampleGraph", true);
    int choice;
    string nodeName, fromNode, toNode, filename;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Введите имя узла: ";
            getline(cin, nodeName);
            graph.addNode(nodeName);
            break;
        case 2:
            cout << "Введите имя узла для удаления: ";
            getline(cin, nodeName);
            graph.removeNode(nodeName);
            break;
        case 3:
            cout << "Введите узел 'от': ";
            getline(cin, fromNode);
            cout << "Введите узел 'до': ";
            getline(cin, toNode);
            graph.addEdge(fromNode, toNode);
            break;
        case 4:
            cout << "Введите узел 'от' для удаления: ";
            getline(cin, fromNode);
            cout << "Введите узел 'до' для удаления: ";
            getline(cin, toNode);
            graph.removeEdge(fromNode, toNode);
            break;
        case 5:
            graph.displayInfo();
            break;
        case 6:
            cout << "Введите имя файла для экспорта: ";
            getline(cin, filename);
            graph.exportGraph(filename);
            break;
        case 7:
            cout << "Введите имя файла для импорта: ";
            getline(cin, filename);
            graph.importGraph(filename);
            break;
        case 8:
            graph.drawGraph();
            break;
        case 9:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }

    return 0;
}

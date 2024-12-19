#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

struct Edge {
    string from, to;
    bool directed;

    Edge(const string& from, const string& to, bool directed)
        : from(from), to(to), directed(directed) {}
};

void addNode(map<string, set<string>>& adjacencyList, const string& node) {
    if (adjacencyList.find(node) == adjacencyList.end()) {
        adjacencyList[node] = set<string>();
        cout << "Узел '" << node << "' добавлен.\n";
    } else {
        cout << "Узел '" << node << "' уже существует.\n";
    }
}

void removeNode(map<string, set<string>>& adjacencyList, vector<Edge>& edges, const string& node) {
    if (adjacencyList.find(node) != adjacencyList.end()) {
        adjacencyList.erase(node);
        edges.erase(remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
            return edge.from == node || edge.to == node;
        }), edges.end());
        cout << "Узел '" << node << "' удалён.\n";
    } else {
        cout << "Узел '" << node << "' не найден.\n";
    }
}

void addEdge(vector<Edge>& edges, map<string, set<string>>& adjacencyList, const string& from, const string& to, bool directed) {
    if (adjacencyList.find(from) != adjacencyList.end() && adjacencyList.find(to) != adjacencyList.end()) {
        adjacencyList[from].insert(to);
        if (!directed) {
            adjacencyList[to].insert(from);
        }
        edges.emplace_back(from, to, directed);
        cout << "Ребро от '" << from << "' до '" << to << "' добавлено.\n";
    } else {
        cout << "Один или оба узла не существуют.\n";
    }
}

void removeEdge(vector<Edge>& edges, map<string, set<string>>& adjacencyList, const string& from, const string& to, bool directed) {
    if (adjacencyList.find(from) != adjacencyList.end() && adjacencyList.find(to) != adjacencyList.end()) {
        adjacencyList[from].erase(to);
        if (!directed) {
            adjacencyList[to].erase(from);
        }
        edges.erase(remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
            return edge.from == from && edge.to == to;
        }), edges.end());
        cout << "Ребро от '" << from << "' до '" << to << "' удалено.\n";
    } else {
        cout << "Один или оба узла не существуют.\n";
    }
}

void showInfo(const map<string, set<string>>& adjacencyList, const vector<Edge>& edges) {
    cout << "Количество узлов: " << adjacencyList.size() << ", Количество рёбер: " << edges.size() << endl;
}

void printGraph(const vector<Edge>& edges, bool directed) {
    cout << "\n--- Представление графа ---\n";
    for (const auto& edge : edges) {
        cout << edge.from << " -> " << edge.to << endl;
        if (!directed) {
            cout << edge.to << " -> " << edge.from << endl;
        }
    }
}

void exportGraph(const map<string, set<string>>& adjacencyList, const vector<Edge>& edges, const string& filename, bool directed) {
    ofstream file(filename);
    if (file) {
        file << "Граф: " << (directed ? "Направленный" : "Ненаправленный") << "\n";
        file << "Узлы: ";
        for (const auto& pair : adjacencyList) {
            file << pair.first << " ";
        }
        file << "\nРёбра: ";
        for (const auto& edge : edges) {
            file << edge.from << " -> " << edge.to << " ";
            if (!directed) {
                file << "<-> " << edge.to << " -> " << edge.from << " ";
            }
        }
        file << endl;
        cout << "Граф экспортирован в файл " << filename << endl;
    } else {
        cout << "Ошибка при открытии файла для экспорта.\n";
    }
}

void importGraph(map<string, set<string>>& adjacencyList, vector<Edge>& edges, const string& filename, bool& directed) {
    ifstream file(filename);
    if (file) {
        string line;
        adjacencyList.clear();
        edges.clear();

        getline(file, line);
        directed = line.find("Направленный") != string::npos;

        getline(file, line);
        istringstream nodesStream(line.substr(7));
        string node;
        while (nodesStream >> node) {
            addNode(adjacencyList, node);
        }

        getline(file, line);
        istringstream edgesStream(line.substr(7));
        string from, to;
        while (edgesStream >> from >> to) {
            addEdge(edges, adjacencyList, from, to, directed);
        }

        cout << "Граф импортирован из файла " << filename << endl;
    } else {
        cout << "Ошибка при открытии файла для импорта.\n";
    }
}

void showMenu() {
    cout << "\n1. Добавить узел\n"
         << "2. Удалить узел\n"
         << "3. Добавить ребро\n"
         << "4. Удалить ребро\n"
         << "5. Показать информацию о графе\n"
         << "6. Экспортировать граф\n"
         << "7. Импортировать граф\n"
         << "8. Показать граф\n"
         << "9. Выход\n"
         << "Выберите опцию: ";
}

int main() {
    map<string, set<string>> adjacencyList;
    vector<Edge> edges;
    bool directed = true;
    string node, from, to, filename;
    int option;

    while (true) {
        showMenu();
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (option == 1) {
            cout << "Введите имя узла: ";
            getline(cin, node);
            addNode(adjacencyList, node);
        }
        else if (option == 2) {
            cout << "Введите имя узла для удаления: ";
            getline(cin, node);
            removeNode(adjacencyList, edges, node);
        }
        else if (option == 3) {
            cout << "Введите начальный узел: ";
            getline(cin, from);
            cout << "Введите конечный узел: ";
            getline(cin, to);
            addEdge(edges, adjacencyList, from, to, directed);
        }
        else if (option == 4) {
            cout << "Введите начальный узел для удаления ребра: ";
            getline(cin, from);
            cout << "Введите конечный узел для удаления ребра: ";
            getline(cin, to);
            removeEdge(edges, adjacencyList, from, to, directed);
        }
        else if (option == 5) {
            showInfo(adjacencyList, edges);
        }
        else if (option == 6) {
            cout << "Введите имя файла для экспорта: ";
            getline(cin, filename);
            exportGraph(adjacencyList, edges, filename, directed);
        }
        else if (option == 7) {
            cout << "Введите имя файла для импорта: ";
            getline(cin, filename);
            importGraph(adjacencyList, edges, filename, directed);
        }
        else if (option == 8) {
            printGraph(edges, directed);
        }
        else if (option == 9) {
            break;
        } else {
            cout << "Неверная опция, попробуйте снова.\n";
        }
    }

    return 0;
}

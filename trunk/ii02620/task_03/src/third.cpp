#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

class Vertex {
public:
    string title;
    string data;
    string link;

    Vertex() = default;
    Vertex(const string& vertexTitle) : title(vertexTitle) {}
};

class Connection {
public:
    string start;
    string end;
    bool isDirected;

    Connection(const string& start, const string& end, bool directed = false)
        : start(start), end(end), isDirected(directed) {}
};

class Network {
public:
    string title;
    bool isDirected;
    unordered_map<string, Vertex> vertices;
    vector<Connection> connections;

    Network(const string& networkTitle, bool directed)
        : title(networkTitle), isDirected(directed) {}

    void addVertex(const string& vertexTitle) {
        if (vertices.find(vertexTitle) == vertices.end()) {
            vertices[vertexTitle] = Vertex(vertexTitle);
            cout << "Узел " << vertexTitle << " добавлен." << endl;
        }
        else {
            cout << "Узел " << vertexTitle << " уже существует." << endl;
        }
    }

    void removeVertex(const string& vertexTitle) {
        if (vertices.erase(vertexTitle)) {
            connections.erase(remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
                return connection.start == vertexTitle || connection.end == vertexTitle;
                }), connections.end());
            cout << "Узел " << vertexTitle << " удалён." << endl;
        }
        else {
            cout << "Узел " << vertexTitle << " не существует." << endl;
        }
    }

    void addConnection(const string& start, const string& end) {
        if (vertices.find(start) != vertices.end() && vertices.find(end) != vertices.end()) {
            connections.emplace_back(start, end, isDirected);
            cout << "Ребро от " << start << " до " << end << " добавлено." << endl;
        }
        else {
            cout << "Одно или оба узла не существует." << endl;
        }
    }

    void removeConnection(const string& start, const string& end) {
        connections.erase(remove_if(connections.begin(), connections.end(), [&](Connection& connection) {
            return connection.start == start && connection.end == end;
            }), connections.end());
        cout << "Ребро от " << start << " до " << end << " удалено." << endl;
    }

    void exportNetwork(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << title << " : " << (isDirected ? "ориентированный" : "неориентированный") << " ;" << endl;
            for (const auto& vertexPair : vertices) {
                outFile << vertexPair.first << " ";
            }
            outFile << ";" << endl;
            for (const auto& connection : connections) {
                outFile << connection.start << " -> " << connection.end << " ;" << endl;
            }
            outFile.close();
            cout << "Граф экспортирован в " << filename << endl;
        }
        else {
            cout << "Ошибка при открытии файла для экспорта." << endl;
        }
    }

    void importNetwork(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            vertices.clear();
            connections.clear();
            string line;
            getline(inFile, line);
            size_t pos = line.find(" : ");
            title = line.substr(0, pos);
            isDirected = line.find("ориентированный") != string::npos;

            getline(inFile, line);
            pos = 0;
            while ((pos = line.find(' ')) != string::npos) {
                string vertexTitle = line.substr(0, pos);
                addVertex(vertexTitle);
                line.erase(0, pos + 1);
            }
            if (!line.empty()) addVertex(line);

            while (getline(inFile, line)) {
                pos = line.find(" -> ");
                if (pos != string::npos) {
                    string start = line.substr(0, pos);
                    line.erase(0, pos + 4);
                    pos = line.find(" ;");
                    string end = line.substr(0, pos);
                    addConnection(start, end);
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
        cout << "Граф: " << title << endl;
        cout << "Количество узлов: " << vertices.size() << endl;
        cout << "Количество рёбер: " << connections.size() << endl;
    }

    void drawNetwork() {
        cout << endl << "--- Представление графиков в формате ASCII ---" << endl;
        for (const auto& connection : connections) {
            cout << setw(2) << connection.start << " --> " << connection.end << endl;
            if (!isDirected) {
                cout << setw(2) << connection.end << " --> " << connection.start << endl;
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
    Network network("ExampleNetwork", true);
    int choice;
    string vertexTitle, startVertex, endVertex, filename;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Введите имя узла: ";
            getline(cin, vertexTitle);
            network.addVertex(vertexTitle);
            break;
        case 2:
            cout << "Введите имя узла для удаления: ";
            getline(cin, vertexTitle);
            network.removeVertex(vertexTitle);
            break;
        case 3:
            cout << "Введите узел 'от': ";
            getline(cin, startVertex);
            cout << "Введите узел 'до': ";
            getline(cin, endVertex);
            network.addConnection(startVertex, endVertex);
            break;
        case 4:
            cout << "Введите узел 'от' для удаления: ";
            getline(cin, startVertex);
            cout << "Введите узел 'до' для удаления: ";
            getline(cin, endVertex);
            network.removeConnection(startVertex, endVertex);
            break;
        case 5:
            network.displayInfo();
            break;
        case 6:
            cout << "Введите имя файла для экспорта: ";
            getline(cin, filename);
            network.exportNetwork(filename);
            break;
        case 7:
            cout << "Введите имя файла для импорта: ";
            getline(cin, filename);
            network.importNetwork(filename);
            break;
        case 8:
            network.drawNetwork();
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
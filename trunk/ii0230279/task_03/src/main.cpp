#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>
#include <set>
#include <memory>

// ����� ��� ������������� ���� �����
class Node {
public:
    std::string name; // ��� ����

    Node(const std::string& nodeName) : name(nodeName) {}
};

// ����� ��� ������������� ����� �����
class Edge {
public:
    std::string start;
    std::string end;

    Edge(const std::string& from, const std::string& to) : start(from), end(to) {}
};

// ����� ��� ������������� �����
class GraphRepresentation {
private:
    std::string graphName; // �������� �����
    bool isDirected; // �������� �� ���� ���������������
    std::set<std::string> nodeSet; // ����� �����
    std::vector<Edge> edgeList; // ������ ����

public:
    GraphRepresentation(const std::string& name, bool directed) : graphName(name), isDirected(directed) {}

    // ����� ��� ���������� ����
    void addNode(const std::string& nodeName) {
        auto result = nodeSet.insert(nodeName);
        if (result.second) {
            std::cout << "���� \"" << nodeName << "\" ��������.\n";
        }
        else {
            std::cout << "���� \"" << nodeName << "\" ��� ����������.\n";
        }
    }

    // ����� ��� �������� ����
    void removeNode(const std::string& nodeName) {
        auto erased = nodeSet.erase(nodeName);
        if (erased) {
            edgeList.erase(std::remove_if(edgeList.begin(), edgeList.end(), [&](const Edge& edge) {
                return edge.start == nodeName || edge.end == nodeName;
                }), edgeList.end());
            std::cout << "���� \"" << nodeName << "\" �����.\n";
        }
        else {
            std::cout << "���� \"" << nodeName << "\" �� ������.\n";
        }
    }

    // ����� ��� ���������� �����
    void addEdge(const std::string& from, const std::string& to) {
        if (nodeSet.count(from) && nodeSet.count(to)) {
            edgeList.emplace_back(from, to);
            std::cout << "����� ��������� �� \"" << from << "\" � \"" << to << "\".\n";
        }
        else {
            std::cout << "���� ��� ��� ���� �� ����������.\n";
        }
    }

    // ����� ��� �������� �����
    void removeEdge(const std::string& from, const std::string& to) {
        edgeList.erase(std::remove_if(edgeList.begin(), edgeList.end(), [&](const Edge& edge) {
            return edge.start == from && edge.end == to;
            }), edgeList.end());
        std::cout << "����� ������� �� \"" << from << "\" � \"" << to << "\".\n";
    }

    // ����� ��� ����������� ���������� � �����
    void displayInfo() const {
        std::cout << "���� \"" << graphName << "\" �������� " << nodeSet.size() << " ����� � " << edgeList.size() << " ����.\n";
    }

    // ����� ��� ���������� ����� � ����
    void saveGraphToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << graphName << " : " << (isDirected ? "���������������" : "�����������������") << "\n";
            for (const auto& node : nodeSet) {
                outFile << node << " ";
            }
            outFile << ";\n";

            for (const auto& edge : edgeList) {
                outFile << edge.start << " -> " << edge.end << " ";
            }
            outFile << "\n"; // ��������� ������
            outFile.close();
            std::cout << "���� ������� � ���� \"" << filename << "\".\n";
        }
        else {
            std::cout << "�� ������� ������� ���� ��� ������.\n";
        }
    }

    // ����� ��� �������� ����� �� �����
    void loadGraphFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            nodeSet.clear();
            edgeList.clear();
            std::string line;

            std::getline(inFile, line);
            graphName = line.substr(0, line.find(" : "));
            isDirected = line.find("���������������") != std::string::npos;

            std::getline(inFile, line);
            std::istringstream nodeStream(line);
            std::string nodeName;
            while (nodeStream >> nodeName) {
                if (nodeName != ";") { // ���������� ������ ����� �����
                    addNode(nodeName);
                }
            }

            std::getline(inFile, line);
            std::istringstream edgeStream(line);
            std::string fromNode, toNode;
            while (edgeStream >> fromNode) {
                edgeStream >> std::ws; // ���������� �������
                if (edgeStream.good()) {
                    std::string arrow;
                    edgeStream >> arrow; // ������ "->"
                    if (arrow != "->") break; // ���� � ��� ��� �������, ������� �� �����
                    edgeStream >> toNode;
                    addEdge(fromNode, toNode);
                    edgeStream >> std::ws; // ���������� �������
                }
            }

            inFile.close();
            std::cout << "���� �������� �� ����� \"" << filename << "\".\n";
        }
        else {
            std::cout << "�� ������� ������� ���� ��� ������.\n";
        }
    }

    // ����� ��� ����������� ����� � ASCII
    void drawGraph() const {
        std::cout << "\n--- ���� � ���� ASCII ---\n";
        for (const auto& edge : edgeList) {
            std::cout << edge.start << " --> " << edge.end << "\n";
            if (!isDirected) {
                std::cout << edge.end << " --> " << edge.start << "\n";
            }
        }
        std::cout << "--------------------------\n";
    }
};

// ������� ��� ����������� ����
void showMenu() {
    std::cout << "\n--- ���� ���������� ������ ---\n";
    std::cout << "1. �������� ����\n";
    std::cout << "2. ������� ����\n";
    std::cout << "3. �������� �����\n";
    std::cout << "4. ������� �����\n";
    std::cout << "5. �������� ���������� � �����\n";
    std::cout << "6. ��������� ���� � ����\n";
    std::cout << "7. ��������� ���� �� �����\n";
    std::cout << "8. ���������� ���� (ASCII)\n";
    std::cout << "9. �����\n";
    std::cout << "�������� �����: ";
}

int main() {
    setlocale(LC_ALL, "rus"); // ������������� ����������� ��� �������� �����
    auto graphPtr = std::make_shared<GraphRepresentation>("�����������", true); // ������ ��������� �� ����
    int option; // ���������� ��� �������� ������ ������������
    std::string nodeName, fromNode, toNode, filename; // ���������� ��� ���� ����� � ������

    while (true) { // �������� ���� ���������
        showMenu(); // ���������� ����
        std::cin >> option; // ��������� ����� ������������
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� ���������� ������� � ������

        switch (option) {
        case 1:
            std::cout << "������� ��� ����: ";
            std::getline(std::cin, nodeName); // ��������� ��� ����
            graphPtr->addNode(nodeName); // ��������� ����
            break;

        case 2:
            std::cout << "������� ��� ���� ��� ��������: ";
            std::getline(std::cin, nodeName); // ��������� ��� ����
            graphPtr->removeNode(nodeName); // ������� ����
            break;

        case 3:
            std::cout << "������� ��������� ����: ";
            std::getline(std::cin, fromNode); // ��������� ��������� ����
            std::cout << "������� �������� ����: ";
            std::getline(std::cin, toNode); // ��������� �������� ����
            graphPtr->addEdge(fromNode, toNode); // ��������� �����
            break;

        case 4:
            std::cout << "������� ��������� ���� ��� ��������: ";
            std::getline(std::cin, fromNode); // ��������� ��������� ����
            std::cout << "������� �������� ���� ��� ��������: ";
            std::getline(std::cin, toNode); // ��������� �������� ����
            graphPtr->removeEdge(fromNode, toNode); // ������� �����
            break;

        case 5:
            graphPtr->displayInfo(); // ���������� ���������� � �����
            break;

        case 6:
            std::cout << "������� ��� ����� ��� ����������: ";
            std::getline(std::cin, filename); // ��������� ��� �����
            graphPtr->saveGraphToFile(filename); // ��������� ���� � ����
            break;

        case 7:
            std::cout << "������� ��� ����� ��� ��������: ";
            std::getline(std::cin, filename); // ��������� ��� �����
            graphPtr->loadGraphFromFile(filename); // ��������� ���� �� �����
            break;

        case 8:
            graphPtr->drawGraph(); // ���������� ���� � ASCII
            break;

        case 9:
            std::cout << "����� �� ���������.\n"; // ����� �� ���������
            return 0;

        default:
            std::cout << "������������ �����. ���������� �����.\n"; // ��������� ������������� �����
            break;
        }
    }

    return 0; // ���������� ���������
}
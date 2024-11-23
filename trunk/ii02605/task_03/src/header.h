#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <iostream>

// ÷вет дл€ узлов и рЄбер
enum class Color {
    Red, Green, Blue, Black
};

//  ласс узла графа
class Node {
public:
    Node(const std::string& name);
    void setContent(const std::string& content);
    void setLink(const std::string& link);
    void setColor(Color color);

    std::string getName() const;
    std::string getContent() const;
    std::string getLink() const;
    Color getColor() const;

private:
    std::string name;
    std::string content;
    std::string link;
    Color color = Color::Black;
};

//  ласс ребра графа
class Edge {
public:
    Edge(const std::string& node1, const std::string& node2, bool directed = false);
    void setColor(Color color);

    std::pair<std::string, std::string> getNodes() const;
    bool isDirected() const;
    Color getColor() const;

private:
    std::pair<std::string, std::string> nodes;
    bool directed;
    Color color = Color::Black;
};

//  ласс графа
class Graph {
public:
    enum class Type { ORIENTED, UNORIENTED };

    Graph(const std::string& name, Type type);
    ~Graph();

    void addNode(const std::string& nodeName);
    void removeNode(const std::string& nodeName);
    void addEdge(const std::string& node1, const std::string& node2, bool directed = true);
    void removeEdge(const std::string& node1, const std::string& node2);

    void setNodeContent(const std::string& nodeName, const std::string& content);
    void setNodeColor(const std::string& nodeName, Color color);
    void setEdgeColor(const std::string& node1, const std::string& node2, Color color);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    void printGraphInfo() const;

private:
    std::string name;
    Type type;
    std::map<std::string, Node> nodes;
    std::map<std::pair<std::string, std::string>, Edge> edges;
};

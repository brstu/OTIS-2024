# Лабораторная работа 3

В ходе лабораторной работы реализовал программу для взаимодействия с графами

```C++
class Graph {
private:
    std::string name;
    std::unordered_map<std::string, Node> nodes; // узлы графа
    std::vector<Edge> edges; // ребра графа
    bool directed;
    
    
void addNode(const std::string &nodeName) {
    ....
}
void addEdge(const std::string &from, const std::string &to) {
    ....
}
 void removeNode(const std::string &nodeName) {
    ....
}
```
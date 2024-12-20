### Лабораторная работа 3
## Граф
## Учащийся группы ИИ-25
## Янушкевич Вячеслав Александрович
## Class
```C++
class Edge {
public:
    Node* start;
    Node* end;
    bool directed;

    Edge(Node* start, Node* end, bool directed)
        : start(start), end(end), directed(directed) {}
};

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
```

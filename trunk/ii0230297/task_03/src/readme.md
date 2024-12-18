### Лабораторная работа №3
#### Графы
####  Скачков Евгений Владимирович
#### Для чего нужен этот код
Реализовывает программу, позволяющую редактировать графовые конструкции различных видов и производить над ними различные действия
#### Функция данного кода
Функция addNode добавляет узел
```C++
void addEdge(const std::string& fromName, const std::string& toName, bool directed) {
        auto fromNode = findNode(fromName);
        auto toNode = findNode(toName);
        if (fromNode && toNode) {
            edges.push_back(std::make_shared<Edge>(fromNode, toNode, directed));
        }
    }
```

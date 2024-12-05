### Лабораторная работа №3
#### Графы
####  Скачков Евгений Владимирович
#### Для чего нужен этот код
Реализовывает программу, позволяющую редактировать графовые конструкции различных видов и производить над ними различные действия
#### Функция данного кода
Функция addNode добавляет узел, а removeNode наоборот удаляет уезл из графа по его имени
```C++
void addNode(const std::string& name) {
        nodes.push_back(new Node(name));
    }
    void removeNode(const std::string& name) {
        auto it = std::remove_if(nodes.begin(), nodes.end(), [&](Node* n) { return n->name == name; });
        nodes.erase(it, nodes.end());

    }
```

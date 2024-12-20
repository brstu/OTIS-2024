<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Применение знаний алгоритмов для графов на практике”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Кулик Я.А.</p>
<p align="right">Проверила:</p>
<p align="right">Ситковец Я.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

---

# Общее задание #
1. Разработать и реализовать программный продукт позволяющий
редактировать графовые конструкции различных видов и производить над
ними различные действия. Язык программирования - любой.

2. Редактор должен позволять (задания со **[\*]** являются необязательными):  
  a) одновременно работать с несколькими графами (MDI);  
  b) **[\*]** выделение одновременно нескольких элементов графа, копирование
выделенного фрагмента в clipboard и восстановление из него;  
  c) задавать имена графам;  
  d) сохранять и восстанавливать граф во внутреннем формате программы;  
  e) экспортировать и импортировать граф в текстовый формат (описание
см. ниже);  
  f) создавать, удалять, именовать, переименовывать, перемещать узлы;  
  g) создавать ориентированные и неориентированные дуги, удалять дуги;  
  h) добавлять, удалять и редактировать содержимое узла (содержимое в
виде текста и ссылки на файл);  
  i) задавать цвет дуги и узла, образ узла;  
  j) **[\*]** создавать и отображать петли;  
  k) **[\*]** создавать и отображать кратные дуги.

3. Программный продукт должен позволять выполнять следующие операции:  
  a) выводить информацию о графе:

 + количество вершин, дуг;
 + степени для всех вершин и для выбранной вершины;
 + матрицу инцидентности;
 + матрицу смежности;
 + является ли он деревом, полным, связанным, эйлеровым, **[\*]** планарным;

  b) поиск всех путей (маршрутов) между двумя узлами и кратчайших;  
  c) вычисление расстояния между двумя узлами;  
  d) вычисление диаметра, радиуса, центра графа;  
  e) **[\*]** вычисление векторного и декартово произведения двух графов;  
  f) **[\*]** раскраска графа;  
  g) нахождения эйлеровых, [*] гамильтоновых циклов;  
  h) **[\*]** поиск подграфа в графе, со всеми или некоторыми неизвестными
узлами;  
  i) **[\*]** поиск узла по содержимому;  
  j) **[\*]** объединение, пересечение, сочетание и дополнение графов;  
  k) **[\*]** приведение произвольного графа к определенному типу с
минимальными изменениями:

 + бинарное и обычное дерево;
 + полный граф;
 + планарный граф;
 + связанный граф;

4. Формат текстового представления графа:
<ГРАФ> ::= <ИМЯ ГРАФА> : UNORIENT | ORIENT ; <ОПИСАНИЕ УЗЛОВ> ;
<ОПИСАНИЕ СВЯЗЕЙ> .
<ИМЯ ГРАФА> ::= <ИДЕНТИФИКАТОР>
<ОПИСАНИЕ УЗЛОВ> ::= <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …]
<ИМЯ УЗЛА> ::= <ИДЕНТИФИКАТОР>
<ОПИСАНИЕ СВЯЗЕЙ> ::= <ИМЯ УЗЛА> -> <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …] ;
[<ОПИСАНИЕ СВЯЗЕЙ> …]

5. Написать отчет по выполненной лабораторной работе в .md формате (readme.md). Разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**). 

6. Исходный код разработанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.

---

# Выполнение задания #
```С++
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

class Vertex {
public:
    std::string id;
    std::set<std::string> content; // Содержание узла, например, текст, ссылки на файл

    Vertex() : id("") {} // Конструктор по умолчанию
    Vertex(const std::string& id) : id(id) {}
};

class Link {
public:
    std::string source;
    std::string destination;
    bool isDirected;

    Link(const std::string& source, const std::string& destination, bool isDirected)
        : source(source), destination(destination), isDirected(isDirected) {}
};

class Network {
private:
    std::string title;
    std::unordered_map<std::string, Vertex> vertices; // Узлы сети
    std::vector<Link> links; // Ребра сети
    bool directed;

public:
    Network(const std::string& title, bool directed) : title(title), directed(directed) {}

    void insertVertex(const std::string& vertexId) {
        vertices[vertexId] = Vertex(vertexId);
    }

    void insertLink(const std::string& source, const std::string& destination) {
        links.push_back(Link(source, destination, directed));
    }

    void deleteVertex(const std::string& vertexId) {
        vertices.erase(vertexId);
        links.erase(std::remove_if(links.begin(), links.end(), [vertexId](Link& link) {
            return link.source == vertexId || link.destination == vertexId;
            }), links.end());
    }

    void deleteLink(const std::string& source, const std::string& destination) {
        links.erase(std::remove_if(links.begin(), links.end(), [source, destination](Link& link) {
            return link.source == source && link.destination == destination;
            }), links.end());
    }

    void displayInfo() const {
        std::cout << "Network Title: " << title << "\n";
        std::cout << "Vertices: \n";
        for (const auto& vertex : vertices) {
            std::cout << " - " << vertex.first << "\n";
        }
        std::cout << "Links: \n";
        for (const auto& link : links) {
            std::cout << " - " << link.source << (link.isDirected ? " -> " : " -- ") << link.destination << "\n";
        }
    }

    int getVertexCount() const {
        return vertices.size();
    }

    int getLinkCount() const {
        return links.size();
    }

    const std::string& getTitle() const {
        return title;
    }
};

// Пример использования
int main() {
    Network network("MyNetwork", false); // Создание неориентированной сети
    network.insertVertex("A");
    network.insertVertex("B");
    network.insertVertex("C");
    network.insertLink("A", "B");
    network.insertLink("B", "C");

    network.displayInfo();

    std::cout << "Vertex Count: " << network.getVertexCount() << "\n";
    std::cout << "Link Count: " << network.getLinkCount() << "\n";

    network.deleteLink("A", "B");
    network.deleteVertex("C");

    std::cout << "\nAfter some removals:\n";
    network.displayInfo();

    return 0;
}

```





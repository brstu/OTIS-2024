<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Применение знаний алгоритмов для графов на практике”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Мархель А. Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2024</p>

<hr>

#Разработать и реализовать программный продукт, позволяющий редактировать графовые конструкции различных видов и производить над ними различные действия. Язык программирования - C++.

Редактор должен позволять (задания со [*] являются необязательными): a) одновременно работать с несколькими графами (MDI); b) [*] выделение одновременно нескольких элементов графа, копирование выделенного фрагмента в clipboard и восстановление из него; c) задавать имена графам; d) сохранять и восстанавливать граф во внутреннем формате программы; e) экспортировать и импортировать граф в текстовый формат (описание см. ниже); f) создавать, удалять, именовать, переименовывать, перемещать узлы; g) создавать ориентированные и неориентированные дуги, удалять дуги; h) добавлять, удалять и редактировать содержимое узла (содержимое в виде текста и ссылки на файл); i) задавать цвет дуги и узла, образ узла; j) [*] создавать и отображать петли; k) [*] создавать и отображать кратные дуги.

Программный продукт должен позволять выполнять следующие операции: a) выводить информацию о графе:

количество вершин, дуг;
степени для всех вершин и для выбранной вершины;
матрицу инцидентности;
матрицу смежности;
является ли он деревом, полным, связанным, эйлеровым, [*] планарным;
b) поиск всех путей (маршрутов) между двумя узлами и кратчайших; c) вычисление расстояния между двумя узлами; d) вычисление диаметра, радиуса, центра графа; e) [*] вычисление векторного и декартово произведения двух графов; f) [*] раскраска графа; g) нахождения эйлеровых, [*] гамильтоновых циклов; h) [*] поиск подграфа в графе, со всеми или некоторыми неизвестными узлами; i) [*] поиск узла по содержимому; j) [*] объединение, пересечение, сочетание и дополнение графов; k) [*] приведение произвольного графа к определенному типу с минимальными изменениями:

бинарное и обычное дерево;
полный граф;
планарный граф;
связанный граф;
Формат текстового представления графа: <ГРАФ> ::= <ИМЯ ГРАФА> : UNORIENT | ORIENT ; <ОПИСАНИЕ УЗЛОВ> ; <ОПИСАНИЕ СВЯЗЕЙ> . <ИМЯ ГРАФА> ::= <ИДЕНТИФИКАТОР> <ОПИСАНИЕ УЗЛОВ> ::= <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …] <ИМЯ УЗЛА> ::= <ИДЕНТИФИКАТОР> <ОПИСАНИЕ СВЯЗЕЙ> ::= <ИМЯ УЗЛА> -> <ИМЯ УЗЛА> [ , <ИМЯ УЗЛА> …] ; [<ОПИСАНИЕ СВЯЗЕЙ> …]

Написать отчет по выполненной лабораторной работе в .md формате (readme.md). Разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc (где xx - номер группы, yy - номер студента, например ii02102).

Исходный код разработанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.

Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).
<hr>

# Выполнение задания #

Код программы:
```class Node {
public:
    Node(std::string name) : name(name) {}
    std::string getName() const { return name; }
    // Функции для редактирования содержимого узла, установки цвета и т. д.

private:
    std::string name;
    // Дополнительные свойства узла
};

class Edge {
public:
    Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to, bool isDirected = false)
        : from(from), to(to), isDirected(isDirected) {}
    std::shared_ptr<Node> getFrom() const { return from; }
    std::shared_ptr<Node> getTo() const { return to; }
    bool isDirectedEdge() const { return isDirected; }

private:
    std::shared_ptr<Node> from;
    std::shared_ptr<Node> to;
    bool isDirected;
    // Дополнительные свойства рёбер
};

class Graph {
public:
    Graph(std::string name) : name(name) {}
    
    void addNode(const std::string& nodeName) {
        auto node = std::make_shared<Node>(nodeName);
        nodes[nodeName] = node;
        std::cout << "Node " << nodeName << " added.\n";
    }

    void addEdge(const std::string& fromNode, const std::string& toNode, bool isDirected = false) {
        if (nodes.find(fromNode) != nodes.end() && nodes.find(toNode) != nodes.end()) {
            auto edge = std::make_shared<Edge>(nodes[fromNode], nodes[toNode], isDirected);
            edges.push_back(edge);
            std::cout << "Edge from " << fromNode << " to " << toNode << " added.\n";
        } else {
            std::cout << "One or both nodes not found.\n";
        }
    }
    
    void displayGraph() const {
        std::cout << "Graph: " << name << "\nNodes:\n";
        for (typename std::map<std::string, std::shared_ptr<Node>>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
            std::cout << "- " << it->first << "\n";  // it->first — это имя узла
        }

        std::cout << "Edges:\n";
        for (const auto& edge : edges) {
            std::cout << "- " << edge->getFrom()->getName()
                << (edge->isDirectedEdge() ? " -> " : " -- ")
                << edge->getTo()->getName() << "\n";
        }
    }


    // Методы для экспорта, импорта, проверки свойств графа и т. д.

private:
    std::string name;
    std::map<std::string, std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Edge>> edges;
};


```     


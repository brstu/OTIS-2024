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
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-25</p>
<p align="right">Гродзинский А.Д.</p>
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
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>
#include <set>
#include <memory>

// Класс для представления узла графа
class Node {
public:
    std::string name; // Имя узла

    Node(const std::string& nodeName) : name(nodeName) {}
};

// Класс для представления ребра графа
class Edge {
public:
    std::string start;
    std::string end;

    Edge(const std::string& from, const std::string& to) : start(from), end(to) {}
};

// Класс для представления графа
class GraphRepresentation {
private:
    std::string graphName; // Название графа
    bool isDirected; // Является ли граф ориентированным
    std::set<std::string> nodeSet; // Набор узлов
    std::vector<Edge> edgeList; // Список рёбер

public:
    GraphRepresentation(const std::string& name, bool directed) : graphName(name), isDirected(directed) {}

    // Метод для добавления узла
    void addNode(const std::string& nodeName) {
        auto result = nodeSet.insert(nodeName);
        if (result.second) {
            std::cout << "Узел \"" << nodeName << "\" добавлен.\n";
        }
        else {
            std::cout << "Узел \"" << nodeName << "\" уже существует.\n";
        }
    }

    // Метод для удаления узла
    void removeNode(const std::string& nodeName) {
        auto erased = nodeSet.erase(nodeName);
        if (erased) {
            edgeList.erase(std::remove_if(edgeList.begin(), edgeList.end(), [&](const Edge& edge) {
                return edge.start == nodeName || edge.end == nodeName;
                }), edgeList.end());
            std::cout << "Узел \"" << nodeName << "\" удалён.\n";
        }
        else {
            std::cout << "Узел \"" << nodeName << "\" не найден.\n";
        }
    }

    // Метод для добавления ребра
    void addEdge(const std::string& from, const std::string& to) {
        if (nodeSet.count(from) && nodeSet.count(to)) {
            edgeList.emplace_back(from, to);
            std::cout << "Ребро добавлено от \"" << from << "\" к \"" << to << "\".\n";
        }
        else {
            std::cout << "Один или оба узла не существуют.\n";
        }
    }

    // Метод для удаления ребра
    void removeEdge(const std::string& from, const std::string& to) {
        edgeList.erase(std::remove_if(edgeList.begin(), edgeList.end(), [&](const Edge& edge) {
            return edge.start == from && edge.end == to;
            }), edgeList.end());
        std::cout << "Ребро удалено от \"" << from << "\" к \"" << to << "\".\n";
    }

    // Метод для отображения информации о графе
    void displayInfo() const {
        std::cout << "Граф \"" << graphName << "\" содержит " << nodeSet.size() << " узлов и " << edgeList.size() << " рёбер.\n";
    }

    // Метод для сохранения графа в файл
    void saveGraphToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << graphName << " : " << (isDirected ? "ОРИЕНТИРОВАННЫЙ" : "НЕОРИЕНТИРОВАННЫЙ") << "\n";
            for (const auto& node : nodeSet) {
                outFile << node << " ";
            }
            outFile << ";\n";

            for (const auto& edge : edgeList) {
                outFile << edge.start << " -> " << edge.end << " ";
            }
            outFile << "\n"; // Завершаем строку
            outFile.close();
            std::cout << "Граф сохранён в файл \"" << filename << "\".\n";
        }
        else {
            std::cout << "Не удалось открыть файл для записи.\n";
        }
    }

    // Метод для загрузки графа из файла
    void loadGraphFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            nodeSet.clear();
            edgeList.clear();
            std::string line;

            std::getline(inFile, line);
            graphName = line.substr(0, line.find(" : "));
            isDirected = line.find("ОРИЕНТИРОВАННЫЙ") != std::string::npos;

            std::getline(inFile, line);
            std::istringstream nodeStream(line);
            std::string nodeName;
            while (nodeStream >> nodeName) {
                if (nodeName != ";") { // игнорируем символ конца узлов
                    addNode(nodeName);
                }
            }

            std::getline(inFile, line);
            std::istringstream edgeStream(line);
            std::string fromNode, toNode;
            while (edgeStream >> fromNode) {
                edgeStream >> std::ws; // Пропускаем пробелы
                if (edgeStream.good()) {
                    std::string arrow;
                    edgeStream >> arrow; // Читаем "->"
                    if (arrow != "->") break; // Если у нас нет стрелки, выходим из цикла
                    edgeStream >> toNode;
                    addEdge(fromNode, toNode);
                    edgeStream >> std::ws; // Пропускаем пробелы
                }
            }

            inFile.close();
            std::cout << "Граф загружен из файла \"" << filename << "\".\n";
        }
        else {
            std::cout << "Не удалось открыть файл для чтения.\n";
        }
    }

    // Метод для отображения графа в ASCII
    void drawGraph() const {
        std::cout << "\n--- Граф в виде ASCII ---\n";
        for (const auto& edge : edgeList) {
            std::cout << edge.start << " --> " << edge.end << "\n";
            if (!isDirected) {
                std::cout << edge.end << " --> " << edge.start << "\n";
            }
        }
        std::cout << "--------------------------\n";
    }
};

// Функция для отображения меню
void showMenu() {
    std::cout << "\n--- Меню управления графом ---\n";
    std::cout << "1. Добавить узел\n";
    std::cout << "2. Удалить узел\n";
    std::cout << "3. Добавить ребро\n";
    std::cout << "4. Удалить ребро\n";
    std::cout << "5. Показать информацию о графе\n";
    std::cout << "6. Сохранить граф в файл\n";
    std::cout << "7. Загрузить граф из файла\n";
    std::cout << "8. Отобразить граф (ASCII)\n";
    std::cout << "9. Выход\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "rus"); // Устанавливаем локализацию для русского языка
    auto graphPtr = std::make_shared<GraphRepresentation>("ПримерГрафа", true); // Создаём указатель на граф
    int option; // Переменная для хранения выбора пользователя
    std::string nodeName, fromNode, toNode, filename; // Переменные для имен узлов и файлов

    while (true) { // Основной цикл программы
        showMenu(); // Отображаем меню
        std::cin >> option; // Считываем выбор пользователя
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем оставшиеся символы в буфере

        switch (option) {
        case 1:
            std::cout << "Введите имя узла: ";
            std::getline(std::cin, nodeName); // Считываем имя узла
            graphPtr->addNode(nodeName); // Добавляем узел
            break;

        case 2:
            std::cout << "Введите имя узла для удаления: ";
            std::getline(std::cin, nodeName); // Считываем имя узла
            graphPtr->removeNode(nodeName); // Удаляем узел
            break;

        case 3:
            std::cout << "Введите начальный узел: ";
            std::getline(std::cin, fromNode); // Считываем начальный узел
            std::cout << "Введите конечный узел: ";
            std::getline(std::cin, toNode); // Считываем конечный узел
            graphPtr->addEdge(fromNode, toNode); // Добавляем ребро
            break;

        case 4:
            std::cout << "Введите начальный узел для удаления: ";
            std::getline(std::cin, fromNode); // Считываем начальный узел
            std::cout << "Введите конечный узел для удаления: ";
            std::getline(std::cin, toNode); // Считываем конечный узел
            graphPtr->removeEdge(fromNode, toNode); // Удаляем ребро
            break;

        case 5:
            graphPtr->displayInfo(); // Отображаем информацию о графе
            break;

        case 6:
            std::cout << "Введите имя файла для сохранения: ";
            std::getline(std::cin, filename); // Считываем имя файла
            graphPtr->saveGraphToFile(filename); // Сохраняем граф в файл
            break;

        case 7:
            std::cout << "Введите имя файла для загрузки: ";
            std::getline(std::cin, filename); // Считываем имя файла
            graphPtr->loadGraphFromFile(filename); // Загружаем граф из файла
            break;

        case 8:
            graphPtr->drawGraph(); // Отображаем граф в ASCII
            break;

        case 9:
            std::cout << "Выход из программы.\n"; // Выход из программы
            return 0;

        default:
            std::cout << "Недопустимый выбор. Попробуйте снова.\n"; // Обработка некорректного ввода
            break;
        }
    }

    return 0; // Завершение программы
}
```


![Вывод:](add_adj.png)


![Вывод:](add_nodes.png)


![Вывод:](change_w.png)


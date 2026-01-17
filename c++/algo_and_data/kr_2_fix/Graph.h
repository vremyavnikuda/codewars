#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <string>

// Подключаем Windows API для работы с цветами и кодировкой
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Константы
const int INF = INT_MAX / 2;

enum GraphType
{
    DIRECTED,
    UNDIRECTED
};

enum GraphForm
{
    ADJ_MATRIX,
    ADJ_LIST
};

enum ConsoleColor
{
    COLOR_DEFAULT = 7,
    COLOR_PATH = 10,
    COLOR_NODE = 11,
    COLOR_INF = 8
};

class Graph
{
private:
    int numVertices;
    vector<vector<int>> adjMatrix;
    GraphType type;
    GraphForm form;

    void SetColor(int colorCode) const;
    void validateVertex(int v) const;
    void visualizeInternal(const vector<int> &highlightPath) const;

public:
    // Конструктор
    Graph(int vertices, GraphType gType, GraphForm gForm);

    // Количество вершин
    int V() const;

    // Количество ребер
    int E() const;

    // Добавление ребра (по умолчанию вес 1)
    void Insert(int v1, int v2);

    // Удаление ребра
    void Delete(int v1, int v2);

    // Проверка наличия ребра
    bool Edge(int v1, int v2) const;

    // Получение веса ребра
    int GetEdgeWeight(int v1, int v2) const;

    // Установка веса ребра
    void SetEdge(int v1, int v2, int weight);

    // Печать матрицы (Show)
    void Show() const;

    // Задача (вариант 7): диаметр графа + визуализация
    void Task(bool enableVisualization = false);
};

#endif // GRAPH_H

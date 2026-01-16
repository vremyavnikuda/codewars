// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <limits>

template <typename WeightType>
class Graph
{
private:
    int vertices;                 // число вершин
    int edges;                    // число ребер
    WeightType **adjacencyMatrix; // матрица смежности (M-граф)
    WeightType infinity;          // "бесконечность" для отсутствующих ребер

    // Для Флойда
    WeightType **distanceMatrix;
    int **nextVertexMatrix;

public:
    Graph(int vertices,
          WeightType inf = std::numeric_limits<WeightType>::max() / static_cast<WeightType>(4));
    ~Graph();

    // Операции АТД
    int V() const;
    int E() const;
    bool Insert(int v1, int v2, WeightType weight);
    bool Delete(int v1, int v2);
    bool Edge(int v1, int v2) const;
    bool SetEdge(int v1, int v2, WeightType weight);

    // Флойд-Уоршелл
    void floydWarshall();

    // Вариант 7: путь для диаметра (максимальный исходящий эксцентриситет)
    int *Task(int &pathLength);

    // Показ структуры
    void Show() const;
};

template <typename WeightType>
Graph<WeightType>::Graph(int vertices, WeightType inf)
    : vertices(vertices), edges(0), infinity(inf)
{
    // Матрица смежности: по методичке/примеру на диагонали тоже "нет ребра" => ∞
    adjacencyMatrix = new WeightType *[vertices];
    for (int i = 0; i < vertices; i++)
    {
        adjacencyMatrix[i] = new WeightType[vertices];
        for (int j = 0; j < vertices; j++)
        {
            adjacencyMatrix[i][j] = infinity;
        }
    }

    // Матрицы Флойда
    distanceMatrix = new WeightType *[vertices];
    nextVertexMatrix = new int *[vertices];
    for (int i = 0; i < vertices; i++)
    {
        distanceMatrix[i] = new WeightType[vertices];
        nextVertexMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++)
        {
            distanceMatrix[i][j] = infinity;
            nextVertexMatrix[i][j] = -1;
        }
    }
}

template <typename WeightType>
Graph<WeightType>::~Graph()
{
    for (int i = 0; i < vertices; i++)
    {
        delete[] adjacencyMatrix[i];
        delete[] distanceMatrix[i];
        delete[] nextVertexMatrix[i];
    }
    delete[] adjacencyMatrix;
    delete[] distanceMatrix;
    delete[] nextVertexMatrix;
}

template <typename WeightType>
int Graph<WeightType>::V() const
{
    return vertices;
}

template <typename WeightType>
int Graph<WeightType>::E() const
{
    return edges;
}

template <typename WeightType>
bool Graph<WeightType>::Insert(int v1, int v2, WeightType weight)
{
    // простой граф: без петель, без параллельных ребер
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
        return false;

    if (weight == infinity)
        return false;

    if (adjacencyMatrix[v1][v2] != infinity)
        return false;

    adjacencyMatrix[v1][v2] = weight;
    edges++;
    return true;
}

template <typename WeightType>
bool Graph<WeightType>::Delete(int v1, int v2)
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
        return false;

    if (adjacencyMatrix[v1][v2] == infinity)
        return false;

    adjacencyMatrix[v1][v2] = infinity;
    edges--;
    return true;
}

template <typename WeightType>
bool Graph<WeightType>::Edge(int v1, int v2) const
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
        return false;

    return adjacencyMatrix[v1][v2] != infinity;
}

template <typename WeightType>
bool Graph<WeightType>::SetEdge(int v1, int v2, WeightType weight)
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
        return false;

    if (adjacencyMatrix[v1][v2] == infinity)
        return false;

    if (weight == infinity)
        return false;

    adjacencyMatrix[v1][v2] = weight;
    return true;
}

template <typename WeightType>
void Graph<WeightType>::floydWarshall()
{
    // dist[i][j] = вес ребра, если есть, иначе ∞; dist[i][i] = 0
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
            {
                distanceMatrix[i][j] = static_cast<WeightType>(0);
                nextVertexMatrix[i][j] = -1;
            }
            else if (adjacencyMatrix[i][j] != infinity)
            {
                distanceMatrix[i][j] = adjacencyMatrix[i][j];
                nextVertexMatrix[i][j] = j;
            }
            else
            {
                distanceMatrix[i][j] = infinity;
                nextVertexMatrix[i][j] = -1;
            }
        }
    }

    // Флойд
    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (distanceMatrix[i][k] == infinity)
                continue;

            for (int j = 0; j < vertices; j++)
            {
                if (distanceMatrix[k][j] == infinity)
                    continue;

                WeightType cand = distanceMatrix[i][k] + distanceMatrix[k][j];
                if (cand < distanceMatrix[i][j])
                {
                    distanceMatrix[i][j] = cand;
                    nextVertexMatrix[i][j] = nextVertexMatrix[i][k];
                }
            }
        }
    }
}

template <typename WeightType>
int *Graph<WeightType>::Task(int &pathLength)
{
    floydWarshall();

    // Проверка сильной связности (для орграфа): для всех i!=j должно быть достижимо
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i != j && distanceMatrix[i][j] == infinity)
            {
                pathLength = 0;
                return nullptr;
            }
        }
    }

    // Диаметр = max исходящий эксцентриситет:
    // ecc_out(i) = max_j dist[i][j], диаметр = max_i ecc_out(i)
    WeightType diameter = static_cast<WeightType>(-1);
    int startVertex = -1;
    int endVertex = -1;

    for (int i = 0; i < vertices; i++)
    {
        WeightType eccentricity = static_cast<WeightType>(-1);
        int farJ = -1;

        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                continue;

            if (distanceMatrix[i][j] > eccentricity)
            {
                eccentricity = distanceMatrix[i][j];
                farJ = j;
            }
        }

        if (eccentricity > diameter)
        {
            diameter = eccentricity;
            startVertex = i;
            endVertex = farJ;
        }
    }

    if (startVertex == -1 || endVertex == -1)
    {
        pathLength = 0;
        return nullptr;
    }

    // Восстановление пути start -> end через nextVertexMatrix
    int *path = new int[vertices];
    pathLength = 0;

    int current = startVertex;
    while (current != -1 && pathLength < vertices)
    {
        path[pathLength++] = current;

        if (current == endVertex)
            break;

        current = nextVertexMatrix[current][endVertex];
    }

    // На всякий случай: если вдруг восстановление не дошло до endVertex
    if (pathLength == 0 || path[pathLength - 1] != endVertex)
    {
        delete[] path;
        pathLength = 0;
        return nullptr;
    }

    return path;
}

template <typename WeightType>
void Graph<WeightType>::Show() const
{
    auto flags = std::cout.flags();
    auto fill = std::cout.fill();
    std::cout << std::right << std::setfill(' ');

    const int cellWidth = 4;

    auto printMatrix = [&](const char *title, const char *infText)
    {
        std::cout << title << "\n";
        std::cout << std::setw(cellWidth) << "";
        for (int j = 0; j < vertices; j++)
            std::cout << std::setw(cellWidth) << (j + 1);
        std::cout << "\n";

        for (int i = 0; i < vertices; i++)
        {
            std::cout << std::setw(cellWidth) << (i + 1);
            for (int j = 0; j < vertices; j++)
            {
                if (adjacencyMatrix[i][j] == infinity)
                    std::cout << std::setw(cellWidth) << infText;
                else
                    std::cout << std::setw(cellWidth) << adjacencyMatrix[i][j];
            }
            std::cout << "\n";
        }
    };

    // Формат структуры (как в примере): ∞ в пустых клетках, включая диагональ
    printMatrix("Структура M-графа:", "inf");

    std::cout << "\nНа экране:\n";
    // Псевдографический вариант: "-" вместо ∞
    printMatrix("", "-");

    std::cout.flags(flags);
    std::cout.fill(fill);
}

#endif

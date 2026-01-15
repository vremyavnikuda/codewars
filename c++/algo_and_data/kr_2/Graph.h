#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
template <typename WeightType>
class Graph
{
private:
    // количество вершин
    int vertices;
    // количество ребер
    int edges;
    // матрица смежности
    WeightType **adjacencyMatrix;
    // значение "бесконечность" для отсутствующих ребер
    WeightType infinity;
    // Вспомогательные структуры для алгоритма Флойда
    WeightType **distanceMatrix;
    int **nextVertexMatrix;

public:
    // Конструктор и деструктор
    Graph(int vertices, WeightType inf = 1000000000);
    ~Graph();
    // Операции АТД
    int V() const;
    int E() const;
    bool Insert(int v1, int v2, WeightType weight);
    bool Delete(int v1, int v2);
    bool Edge(int v1, int v2) const;
    bool SetEdge(int v1, int v2, WeightType weight);
    // Алгоритм Флойда-Уоршелла
    void floydWarshall();
    // Метод Task() для определения диаметра графа и пути
    int *Task(int &pathLength);
    // Вывод структуры графа
    void Show() const;
};
// Реализация методов шаблонного класса
template <typename WeightType>
Graph<WeightType>::Graph(int vertices, WeightType inf)
    : vertices(vertices), edges(0), infinity(inf)
{
    // Выделяем память для матрицы смежности
    adjacencyMatrix = new WeightType *[vertices];
    for (int i = 0; i < vertices; i++)
    {
        adjacencyMatrix[i] = new WeightType[vertices];
        for (int j = 0; j < vertices; j++)
        {
            adjacencyMatrix[i][j] = (i == j) ? 0 : infinity;
        }
    }
    // Инициализируем матрицы для алгоритма Флойда
    distanceMatrix = new WeightType *[vertices];
    nextVertexMatrix = new int *[vertices];
    for (int i = 0; i < vertices; i++)
    {
        distanceMatrix[i] = new WeightType[vertices];
        nextVertexMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++)
        {
            distanceMatrix[i][j] = adjacencyMatrix[i][j];
            nextVertexMatrix[i][j] = (adjacencyMatrix[i][j] != infinity) ? j : -1;
        }
    }
}
template <typename WeightType>
Graph<WeightType>::~Graph()
{
    // Освобождаем память
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
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
    {
        return false;
    }
    if (adjacencyMatrix[v1][v2] != infinity)
    {
        return false;
    }
    adjacencyMatrix[v1][v2] = weight;
    edges++;
    distanceMatrix[v1][v2] = weight;
    nextVertexMatrix[v1][v2] = v2;
    return true;
}
template <typename WeightType>
bool Graph<WeightType>::Delete(int v1, int v2)
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices)
    {
        return false;
    }
    if (adjacencyMatrix[v1][v2] == infinity)
    {
        return false;
    }
    adjacencyMatrix[v1][v2] = infinity;
    edges--;
    distanceMatrix[v1][v2] = infinity;
    nextVertexMatrix[v1][v2] = -1;
    return true;
}
template <typename WeightType>
bool Graph<WeightType>::Edge(int v1, int v2) const
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices)
    {
        return false;
    }
    return adjacencyMatrix[v1][v2] != infinity;
}
template <typename WeightType>
bool Graph<WeightType>::SetEdge(int v1, int v2, WeightType weight)
{
    if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices || v1 == v2)
    {
        return false;
    }
    if (adjacencyMatrix[v1][v2] == infinity)
    {
        return false;
    }
    adjacencyMatrix[v1][v2] = weight;
    distanceMatrix[v1][v2] = weight;
    return true;
}
template <typename WeightType>
void Graph<WeightType>::floydWarshall()
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            distanceMatrix[i][j] = adjacencyMatrix[i][j];
            if (i != j && adjacencyMatrix[i][j] != infinity)
            {
                nextVertexMatrix[i][j] = j;
            }
            else
            {
                nextVertexMatrix[i][j] = -1;
            }
        }
    }
    // Алгоритм Флойда
    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (distanceMatrix[i][k] != infinity &&
                    distanceMatrix[k][j] != infinity &&
                    distanceMatrix[i][k] + distanceMatrix[k][j] <
                        distanceMatrix[i][j])
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    nextVertexMatrix[i][j] = nextVertexMatrix[i][k];
                }
            }
        }
    }
}
template <typename WeightType>
int *Graph<WeightType>::Task(int &pathLength)
{
    // Сначала применяем алгоритм Флойда
    floydWarshall();
    // Находим диаметр графа
    WeightType diameter = -1;
    int startVertex = -1;
    int endVertex = -1;
    for (int i = 0; i < vertices; i++)
    {
        WeightType eccentricity = -1;
        for (int j = 0; j < vertices; j++)
        {
            if (i != j && distanceMatrix[i][j] != infinity &&
                distanceMatrix[i][j] > eccentricity)
            {
                eccentricity = distanceMatrix[i][j];
            }
        }
        if (eccentricity > diameter)
        {
            diameter = eccentricity;
            for (int j = 0; j < vertices; j++)
            {
                if (i != j && distanceMatrix[i][j] == eccentricity)
                {
                    startVertex = i;
                    endVertex = j;
                    break;
                }
            }
        }
    }
    // граф несвязный
    if (startVertex == -1)
    {
        pathLength = 0;
        return nullptr;
    }
    // startVertex до endVertex
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
    return path;
}
template <typename WeightType>
void Graph<WeightType>::Show() const
{
    std::cout << "Структура M-графа:\n";
    std::cout << " ";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[i][j] == infinity)
            {
                std::cout << "- ";
            }
            else
            {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\nНа экране:\n";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << i << " ";
        bool hasEdges = false;
        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[i][j] != infinity)
            {
                if (hasEdges)
                    std::cout << ", ";
                std::cout << j << " " << adjacencyMatrix[i][j];
                hasEdges = true;
            }
        }
        std::cout << "\n";
    }
}
#endif

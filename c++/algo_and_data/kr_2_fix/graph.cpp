#include "Graph.h"
#include <clocale>

void Graph::SetColor(int colorCode) const
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#else
    (void)colorCode;
#endif
}

void Graph::validateVertex(int v) const
{
    if (v < 0 || v >= numVertices)
    {
        throw out_of_range("Вершина " + to_string(v) + " выходит за пределы диапазона (0-" +
                           to_string(numVertices - 1) + ").");
    }
}

void Graph::visualizeInternal(const vector<int> &highlightPath) const
{
    cout << "\n   ";
    SetColor(COLOR_NODE);
    for (int i = 0; i < numVertices; ++i)
        cout << setw(5) << i;
    SetColor(COLOR_DEFAULT);
    cout << "\n   " << string(numVertices * 5 + 1, '-') << endl;
    for (int i = 0; i < numVertices; ++i)
    {
        SetColor(COLOR_NODE);
        cout << setw(2) << i << " |";
        SetColor(COLOR_DEFAULT);
        for (int j = 0; j < numVertices; ++j)
        {
            bool isPathEdge = false;
            if (!highlightPath.empty())
            {
                for (size_t k = 0; k < highlightPath.size() - 1; ++k)
                {
                    if (highlightPath[k] == i && highlightPath[k + 1] == j)
                    {
                        isPathEdge = true;
                        break;
                    }
                }
            }

            // Вывод матрицы
            if (adjMatrix[i][j] == INF)
            {
                SetColor(COLOR_INF);
                cout << setw(5) << ".";
            }
            else if (isPathEdge)
            {
                SetColor(COLOR_PATH);
                cout << " [" << setw(1) << adjMatrix[i][j] << "]";
            }
            else
            {
                SetColor(COLOR_DEFAULT);
                cout << setw(5) << adjMatrix[i][j];
            }
            SetColor(COLOR_DEFAULT);
        }
        cout << endl;
    }
    SetColor(COLOR_DEFAULT);
    cout << endl;
}

Graph::Graph(int vertices, GraphType gType, GraphForm gForm)
{
    numVertices = vertices;
    type = gType;
    form = gForm;
    // Инициализация матрицы смежности
    adjMatrix = vector<vector<int>>(vertices, vector<int>(vertices, INF));
    for (int i = 0; i < vertices; ++i)
    {
        adjMatrix[i][i] = 0;
    }
}

int Graph::V() const
{
    return numVertices;
}

int Graph::E() const
{
    int count = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (i != j && adjMatrix[i][j] != INF)
            {
                count++;
            }
        }
    }
    return count;
}

void Graph::Insert(int v1, int v2)
{
    validateVertex(v1);
    validateVertex(v2);
    if (v1 == v2)
        throw logic_error("Петля (ребро в себя) не допускается для этого графа.");

    if (adjMatrix[v1][v2] != INF)
    {
        throw logic_error("Ребро " + to_string(v1) + "->" + to_string(v2) + " уже существует.");
    }
    adjMatrix[v1][v2] = 1;
}

void Graph::Delete(int v1, int v2)
{
    validateVertex(v1);
    validateVertex(v2);
    if (adjMatrix[v1][v2] == INF)
    {
        throw logic_error("Ребро " + to_string(v1) + "->" + to_string(v2) + " не существует.");
    }
    adjMatrix[v1][v2] = INF;
}

bool Graph::Edge(int v1, int v2) const
{
    try
    {
        validateVertex(v1);
        validateVertex(v2);
        return adjMatrix[v1][v2] != INF;
    }
    catch (...)
    {
        return false;
    }
}

int Graph::GetEdgeWeight(int v1, int v2) const
{
    validateVertex(v1);
    validateVertex(v2);
    if (adjMatrix[v1][v2] == INF)
    {
        throw logic_error("Ребро отсутствует.");
    }
    return adjMatrix[v1][v2];
}

void Graph::SetEdge(int v1, int v2, int weight)
{
    validateVertex(v1);
    validateVertex(v2);

    if (adjMatrix[v1][v2] == INF)
    {
        throw logic_error("Ребро не существует. Сначала используйте 'Добавить ребро'.");
    }
    if (weight <= 0)
    {
        throw invalid_argument("Вес ребра должен быть положительным.");
    }
    adjMatrix[v1][v2] = weight;
}

void Graph::Show() const
{
    cout << "Матрица смежности графа:" << endl;
    visualizeInternal(vector<int>());
}

void Graph::Task(bool enableVisualization)
{
    if (E() == 0)
    {
        throw logic_error("Граф не содержит ребер.");
    }

    // 1. Алгоритм Флойда-Уоршелла
    vector<vector<int>> dist = adjMatrix;
    vector<vector<int>> pred(numVertices, vector<int>(numVertices, -1));

    // Инициализация предков
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (i != j && adjMatrix[i][j] != INF)
                pred[i][j] = i;
        }
    }

    // Поиск кратчайших путей
    for (int k = 0; k < numVertices; ++k)
    {
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }

    // 2. Поиск диаметра (макс. эксцентриситет)
    int diameter = -1;
    int startNode = -1, endNode = -1;

    for (int i = 0; i < numVertices; ++i)
    {
        int ecc = -1;
        for (int j = 0; j < numVertices; ++j)
        {
            if (i != j && dist[i][j] != INF)
            {
                if (dist[i][j] > ecc)
                    ecc = dist[i][j];
            }
        }

        if (ecc > diameter)
        {
            diameter = ecc;
            startNode = i;

            // ищем вершину на расстоянии диаметра
            for (int j = 0; j < numVertices; ++j)
            {
                if (i != j && dist[i][j] == diameter)
                {
                    endNode = j;
                    break;
                }
            }
        }
    }

    if (diameter == -1)
    {
        cout << "\nДиаметр графа не найден (граф несвязный).\n";
        return;
    }

    // 3. Восстановление пути
    vector<int> path;
    int curr = endNode;
    path.push_back(curr);
    bool possible = true;

    while (curr != startNode)
    {
        int prev = pred[startNode][curr];
        if (prev == -1)
        {
            possible = false;
            break;
        }
        curr = prev;
        path.push_back(curr);
    }

    if (!possible)
    {
        cout << "Невозможно восстановить путь." << endl;
        return;
    }

    reverse(path.begin(), path.end());

    // 4. Вывод найденных результатов
    cout << "\nРезультаты задачи" << endl;
    cout << "Диаметр графа: " << diameter << endl;
    cout << "Самый длинный путь: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        SetColor(COLOR_PATH);
        cout << path[i];
        SetColor(COLOR_DEFAULT);
        if (i < path.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    // 5. Визуализация матрицы с путём
    if (enableVisualization)
    {
        cout << "\nВизуализация пути в матрице" << endl;
        cout << "(ребра пути выделены [скобками] зелёным)" << endl;
        visualizeInternal(path);
    }
}

void menu(Graph &g)
{
    int choice;
    do
    {
        cout << "Меню для 'Граф'" << endl;
        cout << "1. Добавить ребро (Insert)" << endl;
        cout << "2. Удалить ребро (Delete)" << endl;
        cout << "3. Задать вес ребра (SetEdge)" << endl;
        cout << "4. Проверить наличие ребра (Edge)" << endl;
        cout << "5. V и E (V - вершины, E - ребра)" << endl;
        cout << "6. Показать матрицу смежности (Show)" << endl;
        cout << "7. Решить задачу с визуализацией (Task)" << endl;
        cout << "0. Выход" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        try
        {
            int v1, v2, w;
            switch (choice)
            {
            case 1:
                cout << "Введите вершины (начало конец): ";
                cin >> v1 >> v2;
                g.Insert(v1, v2);
                cout << "Ребро добавлено (вес по умолчанию 1)." << endl;
                break;

            case 2:
                cout << "Введите вершины для удаления: ";
                cin >> v1 >> v2;
                g.Delete(v1, v2);
                cout << "Ребро удалено." << endl;
                break;

            case 3:
                cout << "Введите вершины и вес ребра (v1 v2 w): ";
                cin >> v1 >> v2 >> w;
                g.SetEdge(v1, v2, w);
                cout << "Вес ребра установлен." << endl;
                break;

            case 4:
                cout << "Введите вершины: ";
                cin >> v1 >> v2;
                if (g.Edge(v1, v2))
                {
                    int weight = g.GetEdgeWeight(v1, v2);
                    cout << "[ОК] Ребро " << v1 << " -> " << v2 << " существует.";
                    cout << " Его вес: " << weight << endl;
                }
                else
                {
                    cout << "[Нет] Ребро " << v1 << " -> " << v2 << " не существует." << endl;
                }
                break;

            case 5:
                cout << "Вершины (V): " << g.V() << endl;
                cout << "Ребра (E): " << g.E() << endl;
                break;

            case 6:
                g.Show();
                break;

            case 7:
                g.Task(true);
                break;

            case 0:
                cout << "Выход из программы." << endl;
                break;

            default:
                cout << "Неверный ввод, попробуйте снова." << endl;
            }
        }
        catch (const exception &e)
        {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
#endif
            cout << "!!! Ошибка: " << e.what() << endl;
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 7);
#endif
        }

        cout << endl;
    } while (choice != 0);
}

int main()
{
    // Устанавливаем кодировку UTF-8 для корректного ввода/вывода в Windows
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#else
    setlocale(LC_ALL, "");
#endif

    int v;
    cout << "Введите количество вершин в графе (макс. 20): ";
    cin >> v;
    if (v > 20 || v < 1)
    {
        cout << "Ошибка: недопустимое число вершин (допустимо от 1 до 20)." << endl;
        return 1;
    }
    // Создаем ориентированный граф в виде матрицы смежности
    Graph g(v, DIRECTED, ADJ_MATRIX);
    menu(g);
    return 0;
}

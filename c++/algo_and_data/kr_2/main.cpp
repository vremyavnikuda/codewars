#include "Graph.h"
#include <clocale>
#include <iostream>
int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int vertices;
    std::cout << "Введите количество вершин графа: ";
    std::cin >> vertices;
    Graph<float> graph(vertices);
    int choice;
    do
    {
        std::cout << "\n Меню:\n";
        std::cout << "1. Вставить ребро\n";
        std::cout << "2. Удалить ребро\n";
        std::cout << "3. Проверить наличие ребра\n";
        std::cout << "4. Установить вес ребра\n";
        std::cout << "5. Показать структуру графа\n";
        std::cout << "6. Найти диаметр графа и путь\n";
        std::cout << "7. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int v1, v2;
            float weight;
            std::cout << "Введите вершины (v1 v2) и вес ребра: ";
            std::cin >> v1 >> v2 >> weight;
            if (graph.Insert(v1, v2, weight))
            {
                std::cout << "Ребро добавлено.\n";
            }
            else
            {
                std::cout << "Ошибка при добавлении ребра.\n";
            }
            break;
        }
        case 2:
        {
            int v1, v2;
            std::cout << "Введите вершины (v1 v2): ";
            std::cin >> v1 >> v2;
            if (graph.Delete(v1, v2))
            {
                std::cout << "Ребро удалено.\n";
            }
            else
            {
                std::cout << "Ошибка при удалении ребра.\n";
            }
            break;
        }
        case 3:
        {
            int v1, v2;
            std::cout << "Введите вершины (v1 v2): ";
            std::cin >> v1 >> v2;
            if (graph.Edge(v1, v2))
            {
                std::cout << "Ребро существует.\n";
            }
            else
            {
                std::cout << "Ребро не существует.\n";
            }
            break;
        }
        case 4:
        {
            int v1, v2;
            float weight;
            std::cout << "Введите вершины (v1 v2) и новый вес: ";
            std::cin >> v1 >> v2 >> weight;
            if (graph.SetEdge(v1, v2, weight))
            {
                std::cout << "Вес ребра изменен.\n";
            }
            else
            {
                std::cout << "Ошибка при изменении веса ребра.\n";
            }
            break;
        }
        case 5:
            graph.Show();
            break;
        case 6:
        {
            int pathLength;
            int *path = graph.Task(pathLength);
            if (pathLength == 0)
            {
                std::cout << "Диаметр графа не найден (граф несвязный).\n";
            }
            else
            {
                std::cout << "Путь, соответствующий диаметру: ";
                for (int i = 0; i < pathLength; i++)
                {
                    std::cout << path[i];
                    if (i < pathLength - 1)
                    {
                        std::cout << " -> ";
                    }
                }
                std::cout << std::endl;
                delete[] path;
            }
            break;
        }
        case 7:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    } while (choice != 7);
    return 0;
}

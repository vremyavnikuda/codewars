#include <iostream>

// Функция для вывода матрицы
void printMatrix(int **matrix, int M)
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для преобразования матрицы путем построчного вычитания элементов побочной диагонали
void transformMatrix(int **matrix, int M)
{
    // Вычисляем побочную диагональ
    int *diagonal = new int[M];
    for (int i = 0; i < M; ++i)
    {
        diagonal[i] = matrix[i][M - 1 - i];
    }
    // Преобразуем каждую строку матрицы
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            // Вычитаем элемент побочной диагонали из текущего элемента
            matrix[i][j] -= diagonal[j];
        }
    }
    // Освобождаем память, выделенную под побочную диагональ
    delete[] diagonal;
}
int main()
{
    // Размер матрицы
    int M;
    // Запрос размера матрицы у пользователя
    std::cout << "Enter the size of the matrix (M): ";
    std::cin >> M;
    // Создаем матрицу и заполняем ее данными от пользователя
    int **matrix = new int *[M];
    for (int i = 0; i < M; ++i)
    {
        matrix[i] = new int[M];
    }

    // Заполняем матрицу данными от пользователя
    std::cout << "Enter the elements of the matrix:" << std::endl;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cin >> matrix[i][j];
        }
    }
    // Преобразуем матрицу
    transformMatrix(matrix, M);
    // Выводим преобразованную матрицу
    std::cout << "Transformed matrix:" << std::endl;
    printMatrix(matrix, M);

    // Освобождаем память, выделенную под матрицу
    for (int i = 0; i < M; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

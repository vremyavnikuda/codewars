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
    for (int i = 0; i < M; ++i)
    {
        // Элемент побочной диагонали
        int diagonalElement = matrix[i][M - 1 - i];
        for (int j = 0; j < M; ++j)
        {
            matrix[i][j] -= diagonalElement;
        }
    }
}
int main()
{
    int M;
    std::cout << "Enter the size of the matrix (M): ";
    std::cin >> M;
    // Создаем матрицу размером M x M
    int **matrix = new int *[M];
    for (int i = 0; i < M; ++i)
    {
        matrix[i] = new int[M];
    }
    // Вводим элементы матрицы
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
    // Освобождаем память
    for (int i = 0; i < M; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

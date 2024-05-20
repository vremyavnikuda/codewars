#include <iostream>

const int N = 100; // максимальный размер матрицы

// Ввод матрицы
void Enter_Matrix(int Array[][N], int &m, int &n)
{
    std::cout << "Enter Matrix size [M, N]: " << std::endl;
    std::cout << " M: ";
    std::cin >> m;

    std::cout << " N: ";
    std::cin >> n;
    std::cout << "Enter Matrix:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> Array[i][j];
}

// Поиск наибольшего из отрицательных элементов матрицы и его индексов
void Max_Negative(int Array[][N], int m, int n, int &max_negative, int &max_negative_ind_i, int &max_negative_ind_j)
{
    max_negative = -1; // начальное значение для поиска максимального отрицательного элемента
    bool found_negative = false;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Array[i][j] < 0 && (!found_negative || Array[i][j] > max_negative))
            {
                max_negative = Array[i][j];
                max_negative_ind_i = i;
                max_negative_ind_j = j;
                found_negative = true;
            }
        }
    }
    if (!found_negative)
    {
        max_negative = 0; // если отрицательные элементы не найдены
    }
}

int main()
{
    int Matrix[N][N], m, n;
    Enter_Matrix(Matrix, m, n);

    int max_negative, max_negative_ind_i, max_negative_ind_j;
    Max_Negative(Matrix, m, n, max_negative, max_negative_ind_i, max_negative_ind_j);

    if (max_negative < 0)
    {
        std::cout << "Max negative element " << max_negative << std::endl;
        std::cout << "Indexes: [" << max_negative_ind_i << "][" << max_negative_ind_j << "]" << std::endl;
    }
    else
    {
        std::cout << "No negative elements in matrix." << std::endl;
    }
    return 0;
}

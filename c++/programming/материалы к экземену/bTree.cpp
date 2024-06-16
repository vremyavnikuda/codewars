#include <math.h>
#include <iostream>
struct bTree
{
    int value;
    bTree *left, *right;
};

// Функция для проверки ,является ли чисто степенью числа k
bool ifPowerOf(int num, int k)
{
    if (num < 1)
        return false;
    double logResult = log(num) / log(k);

    return floor(logResult) == logResult;
}

// Рекурсивная функция для обхода дерева и подсчета чисел , являющихся степенями числа k.
int countPowersOfK(bTree *root, int k)
{
    if (root == NULL)
        return 0;

    int count = 0;
    if (ifPowerOf(root->value, k))
    {
        count = 1;
    }

    count += countPowersOfK(root->left, k);
    count += countPowersOfK(root->right, k);

    return count;
}

int main()
{
    bTree *root = new bTree{16, NULL, NULL};
    root->left = new bTree{4, NULL, NULL};
    root->right = new bTree{2, NULL, NULL};
    root->left->left = new bTree{64, NULL, NULL};
    root->left->right = new bTree{8, NULL, NULL};

    int k = 2;
    int result = countPowersOfK(root, k);
    std::cout << "Количество чисел, являющихся степенями " << k << ": " << result << std::endl;

    // Освобождение памяти
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}

struct list
{
    char letter;
    struct list *next;
};


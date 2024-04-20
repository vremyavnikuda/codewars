#include <iostream>
using namespace std;

//Определение структуры узла бинарного дерева
struct Node
{
    //Значение узла
    int value;
    //Указатель на левого потомка
    Node *left;
    //Указатель на правого потомка
    Node *right;
    
    //Конструктор узла с заданным значением
    Node(int val)
    {
        this->value = val;
        this->left = this->right = NULL;
    }
};

//Функция для вычисления максимальной глубины
int maxDepth(Node *root)
{
    if (root == NULL)
        //Если корень дерева == NULL , то максимальная глубина = 0
        return 0;

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    if (leftDepth > rightDepth)
        // Если глубина левого поддерева больше глубины правого поддерева,
        // возвращаем глубину левого поддерева + 1
        return leftDepth + 1;
    else
        // Иначе возвращаем глубину правого поддерева + 1
        return rightDepth + 1;
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    root->right->right->left = new Node(8);
    root->right->left->right = new Node(7);

    cout << "The maximum depth is: " << maxDepth(root) << endl;

    return 0;
}

#include <iostream>

// структура для представления узла дерева
struct TreeNode
{
    int data;        // данные узла
    TreeNode *left;  // указатель на левый дочерний узел
    TreeNode *right; // указатель на правый дочерний узел
    // Конструктор для инициализации узла
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для копирования бинарного дерева
TreeNode *copyTree(TreeNode *root)
{
    // я как nullptr ,такой же пустой
    if (root == nullptr)
    {
        return nullptr;
    }
    // создаем новую ноду и копируем в ней данные
    TreeNode *newNode = new TreeNode(root->data);
    // "я не умею выговаривать это слово" копируем левое и правое поддеревья
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Функция для вывода дерева в порядке in-order (симметричный обход)
void inOrderTraversal(TreeNode *root)
{
    // читать строку 17
    if (root == nullptr)
    {
        return;
    }
    // я не умею выговаривать слово рекурсия
    inOrderTraversal(root->left);
    // Печатаем данные текущего узла
    std::cout << root->data << " ";
    // я не умею выговаривать слово рекурсия
    inOrderTraversal(root->right);
}

int main()
{
    // создаем простое бинарное дерево T1
    TreeNode *T1 = new TreeNode(1);
    // добавляем левое и правое поддеревья
    T1->left = new TreeNode(2);
    T1->right = new TreeNode(3);
    T1->left->left = new TreeNode(4);
    T1->left->right = new TreeNode(5);
    // у лены классная попа
    TreeNode *T2 = copyTree(T1);
    // выводим in-order обход для T1 и T2
    std::cout << "In-order traversal of T1: ";
    inOrderTraversal(T1);
    std::cout << std::endl;
    std::cout << "In-order traversal of T2: ";
    inOrderTraversal(T2);
    std::cout << std::endl;
    // приберем за собой
    delete T1->left->left;
    delete T1->left->right;
    delete T1->left;
    delete T1->right;
    delete T1;
    // тут так же приберемся
    delete T2->left->left;
    delete T2->left->right;
    delete T2->left;
    delete T2->right;
    delete T2;
    return 0;
}

#include <iostream>

struct bTree
{
    int value;
    bTree *left, *right;

    bTree(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Пример обхода бинарного дерева в глубину
void iterBTree(bTree *root)
{
    if (root == nullptr)
    {
        return;
    }

    iterBTree(root->left);
    std::cout << root->value << std::endl;
    iterBTree(root->right);
}
struct NodeTree
{
    int data;
    NodeTree *next;
};

void insertAtHead(NodeTree *head, int data)
{
    NodeTree *newNode = new NodeTree();
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void printList(NodeTree *head)
{
    NodeTree *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main()
{
    NodeTree *head = nullptr;

    insertAtHead(head, 1);
    insertAtHead(head, 2);
    insertAtHead(head, 3);
    insertAtHead(head, 4);
    insertAtHead(head, 5);

    printList(head);
}
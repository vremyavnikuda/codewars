#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *findMaxElementAddress(Node *head)
{
    if (head == nullptr)
        return nullptr;

    Node *maxNode = head;
    int maxVal = head->data;
    Node *current = head->next;

    while (current != nullptr)
    {
        if (current->data > maxVal)
        {
            maxVal = current->data;
            maxNode = current;
        }
        current = current->next;
    }

    return maxNode;
}

int main()
{}

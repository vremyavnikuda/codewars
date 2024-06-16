#include <iostream>

struct Node
{
    int data;
    Node *next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList
{
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    void append(int val)
    {
        if (head == nullptr)
        {
            head = new Node(val);
        }
        else
        {
            append(head, val);
        }
    }

    void print()
    {
        print(head);
    }

private:
    void append(Node *node, int val)
    {
        if (node->next == nullptr)
        {
            node->next = new Node(val);
        }
        else
        {
            append(node->next, val);
        }
    }

    void print(Node *node)
    {
        if (node != nullptr)
        {
            std::cout << node->data << " ";
            print(node->next);
        }
    }
};

int main()
{
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.print(); 
    // Output: 1 2 3
    return 0;
}

#include <iostream>

struct List
{
    int value;
    List *next;
    List(int val = 0, List *p = NULL)
    {
        value = val;
        next = p;
    }
};

// Включение элемента в начало списка
List *Insert_first(int n, List *head)
{
    List *q = new List(n, head);
    return q;
}

// Печать содержимого списка
void Print_list(List *head)
{
    List *p = head;
    std::cout << "\nPRINT LIST: ";
    if (p == NULL)
    {
        std::cout << "Список пуст!" << std::endl;
    }
    else
    {
        while (p != NULL)
        {
            std::cout << p->value << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
}

// Функция для нахождения максимального элемента списка и возврата его адреса
List *Find_Max(List *head)
{
    if (head == NULL)
    {
        std::cout << "Список пуст!" << std::endl;
        return NULL;
    }
    List *maxNode = head;
    List *p = head->next;
    while (p != NULL)
    {
        if (p->value > maxNode->value)
        {
            maxNode = p;
        }
        p = p->next;
    }
    return maxNode;
}

// Функция для добавления всех элементов списка L2 после первого вхождения элемента E в список L1
int Add_After_Element(int E, List *L1, List *L2)
{
    List *p = L1;
    while (p != NULL && p->value != E)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        std::cout << "Элемент " << E << " не найден в списке L1." << std::endl;
        return 0;
    }

    List *L2_copy = NULL;
    List *temp = L2;
    while (temp != NULL)
    {
        L2_copy = Insert_first(temp->value, L2_copy);
        temp = temp->next;
    }

    List *L2_reverse = NULL;
    temp = L2_copy;
    while (temp != NULL)
    {
        L2_reverse = Insert_first(temp->value, L2_reverse);
        temp = temp->next;
    }

    List *q = p->next;
    p->next = L2_reverse;

    List *last = L2_reverse;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = q;

    int length = 0;
    p = L1;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }
    return length;
}

int main()
{
    List *L1 = NULL;
    List *L2 = NULL;

    // Пример создания списков
    L1 = Insert_first(3, L1);
    L1 = Insert_first(2, L1);
    L1 = Insert_first(1, L1);

    L2 = Insert_first(5, L2);
    L2 = Insert_first(4, L2);
    L2 = Insert_first(3, L2);
    L2 = Insert_first(2, L2);
    L2 = Insert_first(1, L2);

    // Печать списков
    Print_list(L1);
    Print_list(L2);

    // Нахождение максимального элемента списка L1
    List *maxNode = Find_Max(L1);
    if (maxNode != NULL)
    {
        std::cout << "Максимальный элемент списка L1: " << maxNode->value << std::endl;
    }

    std::cout << std::endl;

    // Добавление элементов L2 в L1 после первого вхождения элемента 2
    int new_length = Add_After_Element(2, L1, L2);
    std::cout << "Длина нового списка L1 после добавления элементов списка L2: " << new_length << std::endl;
    Print_list(L1);

    return 0;
}


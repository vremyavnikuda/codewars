#include <iostream>
#include <fstream>
#include <ctime>
#include <list>

// Структура узла списка
struct Node
{
    int value;
    int count;
    Node *next;

    Node(int v, int c) : value(v), count(c), next(nullptr) {}
};

// Функция для ввода с клавиатуры или генерации случайных чисел и записи в файл
void writeNumbersToFile(const std::string &filename, int count, bool isRandom)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    if (isRandom)
    {
        std::srand(static_cast<unsigned>(std::time(0)));
        for (int i = 0; i < count; ++i)
        {
            int num = std::rand() % 20 - 10;
            file << num << std::endl;
        }
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {
            std::cout << "Enter number " << i + 1 << ": ";
            int num;
            std::cin >> num;
            file << num << std::endl;
        }
    }

    file.close();
}

// Функция для чтения чисел из файла и вывода на экран
void readAndPrintNumbers(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::cout << "Numbers from file:\n";
    int num;
    while (file >> num)
    {
        std::cout << num << " ";
    }
    file.close();
    std::cout << std::endl;
}

// Функция для сортировки списка по возрастанию
void sortListByAscending(Node *&head)
{
    Node **current = &head;
    while (*current != nullptr)
    {
        Node **min = current;
        Node *nextMin = (*current)->next;

        while (nextMin != nullptr)
        {
            if (nextMin->value < (*min)->value)
            {
                min = &nextMin;
            }
            nextMin = nextMin->next;
        }

        std::swap((*current)->value, (*min)->value);
        current = &(*current)->next;
    }
}

// Функция для сортировки списка по убыванию
void sortListByDescending(Node *&head)
{
    Node **current = &head;
    while (*current != nullptr)
    {
        Node **max = current;
        Node *nextMax = (*current)->next;

        while (nextMax != nullptr)
        {
            if (nextMax->value > (*max)->value)
            {
                max = &nextMax;
            }
            nextMax = nextMax->next;
        }

        std::swap((*current)->value, (*max)->value);
        current = &(*current)->next;
    }
}

// Функция для вставки узла в отсортированный список по возрастанию
void insertSorted(Node **tail, Node *node)
{
    if (*tail == nullptr || (*tail)->value >= node->value)
    {
        node->next = *tail;
        *tail = node;
    }
    else
    {
        insertSorted(&((*tail)->next), node);
    }
}

// Функция для вставки узла в отсортированный список по убыванию
void insertSortedDescending(Node **tail, Node *node)
{
    if (*tail == nullptr || (*tail)->value <= node->value)
    {
        node->next = *tail;
        *tail = node;
    }
    else
    {
        insertSortedDescending(&((*tail)->next), node);
    }
}

// Функция для создания упорядоченного списка из чисел файла
Node *createSortedList(const std::string &filename, bool isAscending)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return nullptr;
    }

    Node *head = nullptr;
    Node *tail = nullptr;
    Node *sortedHead = nullptr;
    Node **sortedTail = &sortedHead;
    int num;

    while (file >> num)
    {
        if (head == nullptr || head->value == num)
        {
            if (head == nullptr)
            {
                head = new Node(num, 1);
                tail = head;
            }
            else
            {
                tail->count++;
            }
        }
        else
        {
            tail->next = new Node(num, 1);
            tail = tail->next;
        }
    }
    file.close();

    if (isAscending)
    {
        sortListByAscending(head);
    }
    else
    {
        sortListByDescending(head);
    }

    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        if (isAscending)
        {
            insertSorted(sortedTail, current);
        }
        else
        {
            insertSortedDescending(sortedTail, current);
        }
        current = next;
    }

    // Освобождение памяти, занимаемой оригинальными узлами
    while (head != nullptr)
    {
        Node *next = head->next;
        delete head;
        head = next;
    }

    return sortedHead;
}

// Функция для вывода содержимого списка на экран
void printList(Node *tail)
{
    if (tail == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    std::cout << "Sorted list:\n";
    for (Node *current = tail; current != nullptr; current = current->next)
    {
        std::cout << current->value << "(" << current->count << ") ";
    }
    std::cout << std::endl;
}

// Функция для сортировки содержимого файла
void sortFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::list<int> positiveNumbers;
    std::list<int> negativeNumbers;
    int num;

    while (inputFile >> num)
    {
        if (num > 0)
        {
            positiveNumbers.push_back(num);
        }
        else
        {
            negativeNumbers.push_back(num);
        }
    }
    inputFile.close();

    positiveNumbers.sort();
    negativeNumbers.sort();

    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto &num : positiveNumbers)
    {
        outputFile << num << std::endl;
    }
    for (const auto &num : negativeNumbers)
    {
        outputFile << num << std::endl;
    }

    outputFile.close();
}

// Функция для вывода содержимого файла на экран
void printFileContent(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::cout << "File content:\n";
    int num;

    while (file >> num)
    {
        std::cout << num << " ";
    }
    file.close();
    std::cout << std::endl;
}

// Главная функция
int main()
{
    const std::string filename = "numbers.txt";
    int count = 10;
    bool isRandom = true;

    writeNumbersToFile(filename, count, isRandom);
    readAndPrintNumbers(filename);

    std::cout << "Sorted list (ascending):\n";
    Node *sortedList = createSortedList(filename, true);
    printList(sortedList);

    std::cout << "Sorted list content: \n";
    sortFile(filename);
    printFileContent(filename);

    return 0;
}

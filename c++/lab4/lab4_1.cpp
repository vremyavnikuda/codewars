#include <iostream>
#include <fstream>
#include <ctime>
#include <list>

struct Node
{
    int value;
    int count;
    Node *next;

    Node(int v, int c) : value(v), count(c), next(nullptr) {}
};

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

void printList(Node *head)
{
    if (head == nullptr)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    std::cout << "List:\n";
    for (Node *current = head; current != nullptr; current = current->next)
    {
        std::cout << current->value << "(" << current->count << ") ";
    }
    std::cout << std::endl;
}

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
    int num;

    std::cout << "Unsorted list:\n";
    while (file >> num)
    {
        std::cout << num << " ";
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
    std::cout << std::endl;
    file.close();

    return head;
}

void sortFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::list<int> numbers;
    int num;
    while (inputFile >> num)
    {
        numbers.push_back(num);
    }
    inputFile.close();

    numbers.sort();

    std::ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto &num : numbers)
    {
        outputFile << num << std::endl;
    }

    outputFile.close();
}

int main()
{
    const std::string filename = "numbers1.txt";
    int count = 10;
    bool isRandom = true;

    writeNumbersToFile(filename, count, isRandom);
    readAndPrintNumbers(filename);

    Node *unsortedList = createSortedList(filename, false);
    std::cout << "Sorted list:\n";
    printList(unsortedList);

    sortFile(filename);
    readAndPrintNumbers(filename);

    return 0;
}

#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
// Структура узла списка
struct Node
{
    int value;  // Значение
    int count;  // Количество повторяющихся значений
    Node *next; // Указатель на следующий узел
    // Конструктор
    Node(int v, int c) : value(v), count(c), next(nullptr) {}
};
// Функция для записи чисел в файл
void writeNumbersToFile(const std::string &filename, int count, bool isRandom)
{
    // Открываем файл для записи
    std::ofstream file(filename);
    if (!file.is_open())
    {
        // Если не удалось открыть файл, то выводим сообщение об ошибке
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    if (isRandom)
    {
        // Генерируем случайные числа
        std::srand(static_cast<unsigned>(std::time(0)));
        for (int i = 0; i < count; ++i)
        {
            int num = std::rand() % 20 - 10;
            file << num << std::endl;
        }
    }
    else
    {
        // Читаем числа от пользователя
        for (int i = 0; i < count; ++i)
        {
            std::cout << "Enter number " << i + 1 << ": ";
            int num;
            std::cin >> num;
            file << num << std::endl;
        }
    }
    // Закрываем файл
    file.close();
}
// Функция для чтения чисел из файла и вывода на экран
void readAndPrintNumbers(const std::string &filename)
{
    // Открываем файл для чтения
    std::ifstream file(filename);
    // Проверяем успешность открытия файла
    if (!file.is_open())
    {
        // Выводим сообщение об ошибке если открыть файл не удалось
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Читаем числа из файла
    std::cout << "Numbers from file:\n";
    int num;
    // Выводим числа на экран
    while (file >> num)
    {
        std::cout << num << " ";
    }
    // Закрываем файл после чтения
    file.close();
    std::cout << std::endl;
}

// Функция для вывода содержимого списка на экран
void printList(Node *head)
{
    // Проверяем список на пустоту
    if (head == nullptr)
    {
        // Выводим сообщение об ошибке если список пуст
        std::cout << "List is empty." << std::endl;
        return;
    }

    // Выводим содержимое списка
    std::cout << "List:\n";
    // Перебираем узлы списка
    for (Node *current = head; current != nullptr; current = current->next)
    {
        // Выводим значение и количество повторяющихся значений
        std::cout << current->value << "(" << current->count << ") ";
    }
    // Выводим пустую строку
    std::cout << std::endl;
}
//Функция для создания упорядоченного списка из чисел из файла
Node *createSortedList(const std::string &filename)
{
    // Открываем файл для чтения
    std::ifstream file(filename);
    // Проверяем успешность открытия файла
    if (!file.is_open())
    {
        // В случае чего выводим ошибку ("ну тип файл открыть не удалось")
        std::cerr << "Error opening file: " << filename << std::endl;
        return nullptr;
    }

    // Инициализируем указатели на начало и конец списка
    Node *head = nullptr;
    Node *tail = nullptr;
    int num;

    // Выводим заголовок перед неотсортированным списком
    std::cout << "Unsorted list:\n";
    // Читаем числа из файла и формируем связанный список
    while (file >> num)
    {
        std::cout << num << " ";
        // Проверяем нужно ли создать новый узел или увеличить счетчик
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
    // Закрываем файл после чтения
    file.close();
    return head;
}

// Функция для сортировки содержимого файла
void sortFile(const std::string &filename)
{
    // Открываем файл для чтения
    std::ifstream inputFile(filename);
    // Проверяем успешность открытия файла
    if (!inputFile.is_open())
    {
        // Если файл не удалось открытия то ("туда-сюда,тыры-пыры,ну тип файл открыть не удалось")
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Читаем числа из файла
    std::list<int> numbers;
    int num;
    while (inputFile >> num)
    {
        numbers.push_back(num);
    }
    // Закрываем файл после чтения
    inputFile.close();

    // Сортируем список
    numbers.sort();

    // Открываем файл для записи
    std::ofstream outputFile(filename);
    // Проверяем успешность открытия файла
    if (!outputFile.is_open())
    {
        // Если у тебя не удалось открыть файл, то мне кажется в твоей жизни идет чет не так
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Обрабатываем исключение при записи в файл
    try
    {
        for (const auto &num : numbers)
        {
            // ОК
            outputFile << num << std::endl;
        }
    }
    catch (const std::ios_base::failure &e)
    {
        // Не ОК
        std::cerr << "Error closing file: " << e.what() << std::endl;
    }
    // Всегда закрывай за собой дверь)))
    outputFile.close();
}

// Ну main как main
// Тут тип все по классике ,вызываем все что вызывается и передаем в них все что нам надо)))))))))))))))))))))))))))))))))))))))))))))))))))))
int main()
{
    const std::string filename = "lossser.txt";
    int count = 10;
    bool isRandom = true;

    writeNumbersToFile(filename, count, isRandom);
    readAndPrintNumbers(filename);

    Node *unsortedList = createSortedList(filename);
    std::cout << "Sorted list:\n";
    printList(unsortedList);

    sortFile(filename);
    readAndPrintNumbers(filename);

    return 0;
}
/*
Numbers from file:
-10 5 4 -7 8 6 5 -7 8 3
Unsorted list:
-10 5 4 -7 8 6 5 -7 8 3
Sorted list:
List:
-10(1) 5(1) 4(1) -7(1) 8(1) 6(1) 5(1) -7(1) 8(1) 3(1)
Numbers from file:
-10 -7 -7 3 4 5 5 6 8 8
*/
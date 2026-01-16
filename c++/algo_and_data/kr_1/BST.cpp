#include "BST.h"
#include <iostream>

using namespace std;

void ShowMenu()
{
    cout << "\n МЕНЮ: " << endl;
    cout << "1. Вставка элемента" << endl;
    cout << "2. Удаление элемента" << endl;
    cout << "3. Поиск элемента" << endl;
    cout << "4. Обход дерева (Lt → t → Rt)" << endl;
    cout << "5. Вывод структуры дерева" << endl;
    cout << "6. Опрос размера дерева" << endl;
    cout << "7. Проверка на пустоту" << endl;
    cout << "8. Очистка дерева" << endl;
    cout << "9. Формирование критериев сбалансированности" << endl;
    cout << "10. Работа с итератором" << endl;
    cout << "11. Показать меню" << endl;
    cout << "0. Выход" << endl;
}

void IteratorMenu(BST<int, string> *tree)
{
    BST<int, string>::Iterator it(tree);
    bool exit = false;

    while (!exit)
    {
        cout << "\n Меню итератора" << endl;
        cout << "1. Установить на начало" << endl;
        cout << "2. Переход к следующему" << endl;
        cout << "3. Проверка состояния" << endl;
        cout << "4. Получить данные" << endl;
        cout << "5. Изменить значение через оператор *" << endl; // Улучшенное описание
        cout << "6. Оператор ++" << endl;
        cout << "0. Выход из итератора" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            it.Begin();
            cout << "Итератор установлен на начало" << endl;
            break;

        case 2:
            it.Next();
            cout << "Переход к следующему" << endl;
            break;

        case 3:
            cout << "Итератор за пределами: " << (it.IsOff() ? "да" : "нет") << endl;
            break;

        case 4:
            try
            {
                cout << "Текущее значение: " << *it << endl;
            }
            catch (BSTException &e)
            {
                cout << "Ошибка: " << e.What() << endl;
            }
            break;

        case 5: // ИЗМЕНЕНИЕ ЗНАЧЕНИЯ ЧЕРЕЗ OPERATOR*
            try
            {
                if (it.IsOff())
                {
                    cout << "Невозможно изменить: итератор за пределами!" << endl;
                    break;
                }
                string newValue;
                cout << "Введите новое значение для текущего узла: ";
                cin.ignore();           // игнорируем остаток строки после cin >> choice
                getline(cin, newValue); // поддержка пробелов
                *it = newValue;         // Присваивание через operator*
                cout << "Значение успешно изменено!" << endl;
            }
            catch (BSTException &e)
            {
                cout << "Ошибка: " << e.What() << endl;
            }
            break;

        case 6:
            ++it;
            cout << "Оператор ++ выполнен" << endl;
            break;

        case 0:
            exit = true;
            break;

        default:
            cout << "Неверный выбор" << endl;
        }
    }
}

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // Создание дерева с ключами типа int и данными типа string
    BST<int, string> tree;
    ShowMenu();
    bool exit = false;
    while (!exit)
    {
        cout << "\nВведите номер операции: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        // Вставка
        case 1:
        {
            int key;
            string data;
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите данные: ";
            cin >> data;
            bool result = tree.Insert(key, data);
            cout << (result ? "Элемент успешно вставлен" : "Элемент с таким ключом уже существует") << endl;
            break;
        }
        // Удаление
        case 2:
        {
            int key;
            cout << "Введите ключ для удаления: ";
            cin >> key;
            bool result = tree.Delete(key);
            cout << (result ? "Элемент успешно удален" : "Элемент с таким ключом не найден") << endl;
            break;
        }
        // Поиск
        case 3:
        {
            int key;
            cout << "Введите ключ для поиска: ";
            cin >> key;

            try
            {
                string data = tree.Search(key);
                cout << "Найдено значение: " << data << endl;
            }
            catch (BSTException &e)
            {
                cout << "Ошибка: " << e.What() << endl;
            }
            break;
        }
        // Обход Lt → t → Rt
        case 4:
        {
            cout << "Обход дерева (ключи): ";
            tree.Traverse();
            break;
        }
        // Вывод структуры
        case 5:
        {
            cout << "Структура дерева (значения):" << endl;
            tree.Show();
            break;
        }
        // Размер
        case 6:
        {
            cout << "Размер дерева: " << tree.Size() << endl;
            break;
        }
        // Проверка на пустоту
        case 7:
        {
            cout << "Дерево " << (tree.IsEmpty() ? "пустое" : "не пустое") << endl;
            break;
        }
        // Очистка
        case 8:
        {
            tree.Clear();
            cout << "Дерево очищено" << endl;
            break;
        }
        // Формирование критериев сбалансированности
        case 9:
        {
            tree.UpdateBalance();
            cout << "Критерии сбалансированности обновлены" << endl;
            cout << "Структура дерева с критериями:" << endl;
            tree.Show();
            break;
        }
        // Итератор
        case 10:
        {
            IteratorMenu(&tree);
            break;
        }
        // Показать меню
        case 11:
        {
            ShowMenu();
            break;
        }
        // Выход
        case 0:
        {
            exit = true;
            break;
        }
        default:
            cout << "Неверный выбор" << endl;
        }
    }
    return 0;
}

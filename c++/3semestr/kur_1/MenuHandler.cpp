#include "MenuHandler.h"
#include <iostream>
#include <cstring>

// Выводит меню программы на экран
void MenuHandler::displayMenu() const {
    std::cout << "Menu:\n";
    std::cout << "1. Add a new ad\n";
    std::cout << "2. Delete an ad by logical number\n";
    std::cout << "3. Search by rubric\n";
    std::cout << "4. Search by keyword in text\n";
    std::cout << "5. Sort by date\n";
    std::cout << "6. Save the list to a file\n";
    std::cout << "7. Load the list from a file\n";
    std::cout << "8. Display all ads\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

// Получает выбор пользователя из меню
int MenuHandler::getChoice() const {
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        choice = -1;
    }
    std::cin.ignore();
    return choice;
}

// Запрашивает ввод строки от пользователя
char *MenuHandler::getInput(const char *prompt, size_t size) const {
    char *input = nullptr;
    try {
        input = new char[size];
        std::cout << prompt;
        std::cin.getline(input, size);
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            throw std::ios_base::failure("Invalid input");
        }
    } catch (const std::bad_alloc &e) {
        std::cerr << "memoryAllocationFailedInGetInput: " << e.what() << std::endl;
        throw;
    } catch (const std::ios_base::failure &e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        throw;
    }
    return input;
}

// Обрабатывает выбранный пользователем пункт меню
void MenuHandler::handleChoice(AdList &adList, int choice) const {
    try {
        switch (choice) {
            case 1: {
                char *cat = getInput("Enter category: ", 100);
                char *rub = getInput("Enter rubric: ", 100);
                char *txt = getInput("Enter text: ", 500);
                char *dat = nullptr;

                while (true) {
                    dat = getInput("Enter date (YYYY-MM-DD): ", 11);
                    if (AdList::isValidDate(dat)) {
                        break;
                    }
                    std::cerr << "Invalid date format. Try again.\n";
                    delete[] dat;
                }

                char *phn = getInput("Enter phone: ", 20);
                adList.addAd(cat, rub, txt, dat, phn);

                delete[] cat;
                delete[] rub;
                delete[] txt;
                delete[] dat;
                delete[] phn;
                break;
            }
            case 2: {
                int num;
                std::cout << "Enter logical number to delete: ";
                std::cin >> num;
                if (std::cin.fail() || num < 0) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cerr << "Invalid number.\n";
                    break;
                }
                std::cin.ignore();
                adList.deleteAd(num);
                break;
            }
            case 3: {
                char *rub = getInput("Enter rubric to search: ", 100);
                adList.searchByRubric(rub);
                delete[] rub;
                break;
            }
            case 4: {
                char *keyword = getInput("Enter keyword to search in text: ", 100);
                adList.searchByKeyword(keyword);
                delete[] keyword;
                break;
            }
            case 5: {
                adList.sortAds();
                break;
            }
            case 6: {
                char *filename = getInput("Enter filename to save: ", 100);
                adList.saveToFile(filename);
                delete[] filename;
                break;
            }
            case 7: {
                char *filename = getInput("Enter filename to load: ", 100);
                adList.loadFromFile(filename);
                delete[] filename;
                break;
            }
            case 8: {
                adList.displayAll();
                break;
            }
            case 9: {
                std::cout << "Exiting...\n";
                exit(0);
            }
            default: {
                std::cerr << "Invalid choice.\n";
                break;
            }
        }
    } catch (const std::bad_alloc &e) {
        std::cerr << "memoryAllocationErrorInHandleChoice: " << e.what() << std::endl;
    } catch (const std::ios_base::failure &e) {
        std::cerr << "fileOperationErrorInHandleChoice: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "anErrorOccurredInHandleChoice: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknownErrorOccurredInHandleChoice.\n";
    }
}

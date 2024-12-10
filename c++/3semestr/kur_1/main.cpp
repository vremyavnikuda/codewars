#include "AdList.h"
#include <iostream>


bool isValidDate(const char *date);

int main() {
    AdList adList;

    int choice;
    while (true) {
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
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter category: ";
                    char cat[100];
                    std::cin.getline(cat, 100);

                    std::cout << "Enter rubric: ";
                    char rub[100];
                    std::cin.getline(rub, 100);

                    std::cout << "Enter text: ";
                    char txt[500];
                    std::cin.getline(txt, 500);

                    char dat[11];
                    while (true) {
                        std::cout << "Enter date (YYYY-MM-DD): ";
                        std::cin.getline(dat, 11);

                        if (AdList::isValidDate(dat)) {
                            break;
                        } else {
                            std::cout << "Invalid date format. Please try again." << std::endl;
                        }
                    }

                    std::cout << "Enter phone: ";
                    char phn[20];
                    std::cin.getline(phn, 20);

                    adList.addAd(cat, rub, txt, dat, phn);
                    break;
                }
                case 2: {
                    std::cout << "Enter logical number to delete: ";
                    int num;
                    std::cin >> num;
                    adList.deleteAd(num);
                    std::cin.ignore();
                    break;
                }
                case 3: {
                    std::cout << "Enter rubric to search: ";
                    char rub[100];
                    std::cin.getline(rub, 100);
                    adList.searchByRubric(rub);
                    break;
                }
                case 4: {
                    std::cout << "Enter keyword to search in text: ";
                    char keyword[100];
                    std::cin.getline(keyword, 100);
                    adList.searchByKeyword(keyword);
                    break;
                }
                case 5: {
                    adList.sortAds();
                    break;
                }
                case 6: {
                    std::cout << "Enter filename to save: ";
                    char filename[100];
                    std::cin.getline(filename, 100);
                    adList.saveToFile(filename);
                    std::cout << "List saved to file." << std::endl;
                    break;
                }
                case 7: {
                    std::cout << "Enter filename to load: ";
                    char filename[100];
                    std::cin.getline(filename, 100);
                    adList.loadFromFile(filename);
                    std::cout << "List loaded from file." << std::endl;
                    break;
                }
                case 8: {
                    adList.displayAll();
                    break;
                }
                case 9: {
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
            }
        } catch (const std::bad_alloc &e) {
            std::cerr << "Memory allocation error: " << e.what() << std::endl;
        } catch (const std::ios_base::failure &e) {
            std::cerr << "File operation error: " << e.what() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "An unknown error occurred." << std::endl;
        }
    }
    return 0;
}

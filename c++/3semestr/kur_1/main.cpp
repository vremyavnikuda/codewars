#include "AdList.h"
#include "MenuHandler.h"
#include <iostream>

bool isValidDate(const char *date);

int main() {
    AdList adList;
    MenuHandler menuHandler;

    while (true) {
        menuHandler.displayMenu();
        int choice = menuHandler.getChoice();

        if (choice == -1) {
            std::cerr << "Invalid input. Please enter a number.\n";
            continue;
        }

        try {
            menuHandler.handleChoice(adList, choice);
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

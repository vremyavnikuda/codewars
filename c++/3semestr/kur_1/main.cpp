#include "AdList.h"
#include "MenuHandler.h"
#include <iostream>


int main() {
    AdList adList;
    MenuHandler menuHandler;

    while (true) {
        menuHandler.displayMenu();
        int choice = menuHandler.getChoice();

        if (choice == -1) {
            std::cerr << "invalidInput. pleaseEnterANumber.\n";
            continue;
        }

        try {
            menuHandler.handleChoice(adList, choice);
        } catch (const std::bad_alloc &e) {
            std::cerr << "memoryAllocationError: " << e.what() << std::endl;
        } catch (const std::ios_base::failure &e) {
            std::cerr << "fileOperationError: " << e.what() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "AnErrorOccurred: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "anUnknownErrorOccurred." << std::endl;
        }
    }

    return 0;
}

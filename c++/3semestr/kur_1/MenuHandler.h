#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "AdList.h"

class MenuHandler {
public:
    void displayMenu() const;
    int getChoice() const;
    void handleChoice(AdList &adList, int choice) const;

private:
    char* getInput(const char* prompt, size_t size) const;
};

#endif // MENU_HANDLER_H

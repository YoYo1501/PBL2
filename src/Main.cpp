#include "../include/MainMenu.h"

int main() {
    AuthSystem auth("data/accounts.txt");
    showMainMenu(auth);
    return 0;
}


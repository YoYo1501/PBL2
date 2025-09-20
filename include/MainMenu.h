#ifndef MAINMENU_H
#define MAINMENU_H
#include "AuthSystem.h"

void showMainMenu(AuthSystem& auth);
void handleLogin(AuthSystem& auth);
void handleRegister(AuthSystem& auth);
std::string getHiddenPassword();

#endif

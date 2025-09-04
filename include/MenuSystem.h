#pragma once
#include "AuthSystem.h"

class MenuSystem {
private:
    AuthSystem& auth;

    void menuGuest();      
    void menuStudent();
    void menuManager();

public:
    explicit MenuSystem(AuthSystem& a) : auth(a) {}
    void run();
};

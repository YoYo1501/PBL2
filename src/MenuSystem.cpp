#include "MenuSystem.h"
#include <iostream>
#include <limits>

using std::cout; using std::cin; using std::string;

static void clearCin() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MenuSystem::menuGuest() {
    while (true) {
        cout << "\n===== DORMITORY =====\n";
        cout << "1. Dang ky (Sinh vien)\n";
        cout << "2. Dang ky (Quan ly)\n";
        cout << "3. Dang nhap\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        int c; if(!(cin >> c)){ clearCin(); continue; }
        clearCin();

        if (c == 0) return;
        if (c == 1) {
            string u,p,id;
            cout << "Username: "; std::getline(cin,u);
            cout << "Password: "; std::getline(cin,p);
            cout << "MSSV: ";     std::getline(cin,id);
            if (auth.registerUser(u,p,"student","",id)) cout << "-> Dang ky SV thanh cong!\n";
            else cout << "-> That bai (co the trung username/khong hop le)\n";
        } else if (c == 2) {
            string u,p,name;
            cout << "Username: "; std::getline(cin,u);
            cout << "Password: "; std::getline(cin,p);
            cout << "Ho ten: ";   std::getline(cin,name);
            if (auth.registerUser(u,p,"admin",name)) cout << "-> Dang ky QL thanh cong!\n";
            else cout << "-> That bai (co the trung username/khong hop le)\n";
        } else if (c == 3) {
            string u,p;
            cout << "Username: "; std::getline(cin,u);
            cout << "Password: "; std::getline(cin,p);
            if (!auth.login(u,p)) { cout << "-> Dang nhap that bai!\n"; continue; }
            User* user = auth.getCurrentUser();
            if (user && user->getRole() == "student") { cout << "-> Dang nhap SV thanh cong!\n"; menuStudent(); }
            else { cout << "-> Dang nhap ADMIN thanh cong!\n"; menuManager(); }
        }
    }
}

void MenuSystem::menuStudent() {
    while (true) {
        cout << "\n[SV] 1.Xem thong bao (demo)  0.Dang xuat\nChon: ";
        int c; if(!(cin >> c)){ clearCin(); continue; } clearCin();
        if (c == 0) return;
        if (c == 1) cout << "-> (demo) Chua co thong bao.\n";
    }
}

void MenuSystem::menuManager() {
    while (true) {
        cout << "\n[QL] 1.Quan ly phong (demo)  0.Dang xuat\nChon: ";
        int c; if(!(cin >> c)){ clearCin(); continue; } clearCin();
        if (c == 0) return;
        if (c == 1) cout << "-> (demo) Chuc nang quan ly phong se bo sung sau.\n";
    }
}

void MenuSystem::run() {
    menuGuest();
}

#include "../include/AdminMenu.h"
#include <iostream>
using namespace std;

void AdminMenu::show() {
    int choice;
    do {
        cout << "\n===== MENU QUAN LY (ADMIN) =====\n";
        cout << "1. Quan ly sinh vien\n";
        cout << "2. Quan ly phong\n";
        cout << "3. Quan ly hop dong\n";
        cout << "4. Quan ly hoa don\n";
        cout << "5. Thong ke\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << ">> [TODO] Quan ly sinh vien\n";
            break;
        case 2:
            cout << ">> [TODO] Quan ly phong\n";
            break;
        case 3:
            cout << ">> [TODO] Quan ly hop dong\n";
            break;
        case 4:
            cout << ">> [TODO] Quan ly hoa don\n";
            break;
        case 5:
            cout << ">> [TODO] Thong ke\n";
            break;
        case 0:
            cout << ">> Dang xuat...\n";
            break;
        default:
            cout << ">> Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

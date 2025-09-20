#include "../include/MainMenu.h"
#include "../include/StudentInfo.h"
#include "../include/StudentMenu.h"
#include "../include/AdminMenu.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;

std::string getHiddenPassword() {
    std::string pwd;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == 8) {
            if (!pwd.empty()) {
                pwd.pop_back();
                std::cout << "\b \b";
            }
        } else {
            pwd += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pwd;
}

void handleLogin(AuthSystem& auth) {
    string u, p;
    cout << "Username: "; cin >> u;
    cout << "Password: ";
    p = getHiddenPassword();
    if (auth.login(u, p)) {
        User& current = auth.getCurrentUser();
        if (auth.isAdmin()) {
            AdminMenu am;
            am.show();
        } else if (auth.isStudent()) {
            StudentMenu sm(current, auth);
            sm.show();
        }
    } else {
        cout << ">> Dang nhap that bai!\n";
    }
}

void handleRegister(AuthSystem& auth) {
    string u, p, r;
    cout << "Nhap username: "; cin >> u;
    cout << "Nhap password: ";
    p = getHiddenPassword();
    int roleChoice = 0;
    do {
        cout << "Chon loai tai khoan:\n1. Admin\n2. Student\nLua chon: ";
        cin >> roleChoice;
        if (roleChoice != 1 && roleChoice != 2) cout << "Lua chon khong hop le!\n";
    } while (roleChoice != 1 && roleChoice != 2);
    r = (roleChoice == 1) ? "admin" : "student";
    cin.ignore();
    if (r == "student") {
        StudentInfo info;
        do { cout << "Nhap ho ten: "; getline(cin, info.fullName); if(info.fullName.empty()) cout << "Khong duoc de trong!\n"; } while(info.fullName.empty());
        do { cout << "Nhap gioi tinh: "; getline(cin, info.gender); if(info.gender.empty()) cout << "Khong duoc de trong!\n"; } while(info.gender.empty());
        do { cout << "Nhap que quan: "; getline(cin, info.address); if(info.address.empty()) cout << "Khong duoc de trong!\n"; } while(info.address.empty());
        do { cout << "Nhap ngay sinh (dd/mm/yyyy): "; getline(cin, info.dob); if(info.dob.empty()) cout << "Khong duoc de trong!\n"; } while(info.dob.empty());
        do { cout << "Nhap lop: "; getline(cin, info.classId); if(info.classId.empty()) cout << "Khong duoc de trong!\n"; } while(info.classId.empty());
        do { cout << "Nhap nganh: "; getline(cin, info.major); if(info.major.empty()) cout << "Khong duoc de trong!\n"; } while(info.major.empty());
        do { cout << "Nhap MSSV: "; getline(cin, info.studentId); if(info.studentId.empty()) cout << "Khong duoc de trong!\n"; } while(info.studentId.empty());
        do { cout << "Nhap so dien thoai: "; getline(cin, info.phone); if(info.phone.empty()) cout << "Khong duoc de trong!\n"; } while(info.phone.empty());
        do { cout << "Nhap email: "; getline(cin, info.email); if(info.email.empty()) cout << "Khong duoc de trong!\n"; } while(info.email.empty());
        do { cout << "Nhap dia chi: "; getline(cin, info.addressDetail); if(info.addressDetail.empty()) cout << "Khong duoc de trong!\n"; } while(info.addressDetail.empty());
        do { cout << "Nhap ten ngan hang: "; getline(cin, info.bankName); if(info.bankName.empty()) cout << "Khong duoc de trong!\n"; } while(info.bankName.empty());
        do { cout << "Nhap so tai khoan: "; getline(cin, info.bankAccount); if(info.bankAccount.empty()) cout << "Khong duoc de trong!\n"; } while(info.bankAccount.empty());
        if (auth.registerUser(u, p, r, info.fullName, info.studentId)) {
            std::ofstream infoFile("data/information.txt", std::ios::app);
            if (infoFile.is_open()) {
                infoFile << info.toString() << std::endl;
                infoFile.close();
            }
            cout << ">> Dang ky thanh cong!\n";
        } else {
            cout << ">> Username da ton tai!\n";
        }
    } else {
        string f, sid;
        cout << "Nhap ho ten: "; getline(cin, f);
        cout << "Nhap MSSV: "; getline(cin, sid);
        if (auth.registerUser(u, p, r, f, sid)) {
            cout << ">> Dang ky thanh cong!\n";
        } else {
            cout << ">> Username da ton tai!\n";
        }
    }
}

void showMainMenu(AuthSystem& auth) {
    int choice;
    do {
        cout << "\n===== HE THONG QUAN LY KY TUC XA =====\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;
        switch (choice) {
            case 1: handleLogin(auth); break;
            case 2: handleRegister(auth); break;
            case 0: cout << ">> Thoat chuong trinh!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

#include "../include/MainMenu.h"
#include "../include/StudentInfo.h"
#include "../include/StudentMenu.h"
#include "../include/AdminMenu.h"
#include "../include/Graphics.h"
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
    Graphics::showMainHeader();
    Graphics::showMenuHeader("DANG NHAP HE THONG");
    
    string u = Graphics::getStyledInput("Ten dang nhap");
    
    Graphics::setColor(LIGHTCYAN, BLACK);
    cout << "    >> Mat khau: ";
    Graphics::resetColor();
    string p = getHiddenPassword();
    
    Graphics::showLoadingBar("Dang xac thuc thong tin", 800);
    
    if (auth.login(u, p)) {
        Graphics::showSuccessMessage("Dang nhap thanh cong!");
        User& current = auth.getCurrentUser();
        
        if (auth.isAdmin()) {
            Graphics::pauseWithMessage("Nhan Enter de vao giao dien quan ly...");
            AdminMenu am;
            am.show();
        } else if (auth.isStudent()) {
            Graphics::pauseWithMessage("Nhan Enter de vao giao dien sinh vien...");
            StudentMenu sm(current, auth);
            sm.show();
        }
    } else {
        Graphics::showErrorMessage("Dang nhap that bai! Kiem tra lai thong tin.");
        Graphics::pauseWithMessage();
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
        
        int genderChoice = 0;
        do {
            cout << "Chon gioi tinh:\n1. Nam\n2. Nu\nLua chon: ";
            cin >> genderChoice;
            if (genderChoice != 1 && genderChoice != 2) cout << "Lua chon khong hop le!\n";
        } while (genderChoice != 1 && genderChoice != 2);
        info.gender = (genderChoice == 1) ? "Nam" : "Nu";
        cin.ignore();
        
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
        Graphics::showMainHeader();
        Graphics::showMenuHeader("MENU CHINH");
        
        Graphics::showMenuOption(1, "Dang nhap");
        Graphics::showMenuOption(2, "Dang ky tai khoan");
        Graphics::showMenuSeparator();
        Graphics::showMenuOption(0, "Thoat chuong trinh");
        
        Graphics::showMenuFooter();
        
        Graphics::setColor(YELLOW, BLACK);
        cout << "    >> Lua chon cua ban: ";
        Graphics::setColor(WHITE, BLACK);
        cin >> choice;
        Graphics::resetColor();
        
        switch (choice) {
            case 1: 
                cin.ignore();
                handleLogin(auth); 
                break;
            case 2: 
                cin.ignore();
                handleRegister(auth); 
                break;
            case 0: 
                Graphics::showSuccessMessage("Cam on ban da su dung he thong!");
                Graphics::showLoadingBar("Dang thoat", 500);
                break;
            default: 
                Graphics::showErrorMessage("Lua chon khong hop le!");
                Graphics::pauseWithMessage();
        }
    } while (choice != 0);
}

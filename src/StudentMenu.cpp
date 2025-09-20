#include "../include/models/Contract.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/StudentMenu.h"
#include <iostream>
using namespace std;

void StudentMenu::show() {
    int choice;
    do {
        cout << "\n===== MENU SINH VIEN =====\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Chinh sua thong tin ca nhan\n";
        cout << "3. Xem lich su hop dong\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            currentUser.viewProfile();
            break;
        case 2:
            cin.ignore(); // tránh lỗi xuống dòng
            currentUser.editProfile();
            authSystem.saveUsersToFile(); // lưu thay đổi vào file
            break;
        case 3:
            viewContractHistory();
            break;
        case 0:
            cout << ">> Dang xuat...\n";
            break;
        default:
            cout << ">> Lua chon khong hop le!\n";
        }
    } while (choice != 0);

}

void StudentMenu::viewContractHistory() {
    using std::cout; using std::endl;
    std::ifstream fin("data/contracts.txt");
    if (!fin.is_open()) {
        cout << "Khong the mo file contracts.txt!\n";
        return;
    }
    std::string line;
    std::vector<Contract> contracts;
    while (getline(fin, line)) {
        Contract c = Contract::fromString(line);
        if (c.studentId == currentUser.getStudentId()) {
            contracts.push_back(c);
        }
    }
    fin.close();
    if (contracts.empty()) {
        cout << "Khong co hop dong nao!\n";
        return;
    }
    cout << "\n===== LICH SU HOP DONG =====\n";
    for (const auto& c : contracts) {
        cout << "Ma HD: " << c.contractId << " | Phong: " << c.roomId
             << " | Tu: " << c.startDate << " den: " << c.endDate
             << " | Trang thai: " << c.status << endl;
    }
    cout << "===========================\n";
}


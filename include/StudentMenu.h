    void viewContractHistory(); // Xem lịch sử hợp đồng
#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include "models/User.h"
#include "AuthSystem.h"

class StudentMenu {
private:
    User& currentUser;        // Sinh viên đã login
    AuthSystem& authSystem;   // Để lưu dữ liệu sau khi chỉnh sửa

public:
    StudentMenu(User& u, AuthSystem& auth) : currentUser(u), authSystem(auth) {}
    void show();   // Hiển thị menu sinh viên
    void viewContractHistory(); // Xem lịch sử hợp đồng
};

#endif

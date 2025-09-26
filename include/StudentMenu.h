#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include "models/User.h"
#include "models/Payment.h"
#include "models/Room.h"
#include "AuthSystem.h"

class StudentMenu {
private:
    User& currentUser;        // Sinh viên đã login
    AuthSystem& authSystem;   // Để lưu dữ liệu sau khi chỉnh sửa

public:
    StudentMenu(User& u, AuthSystem& auth) : currentUser(u), authSystem(auth) {}
    void show();   // Hiển thị menu sinh viên
    void viewContractHistory(); // Xem lịch sử hợp đồng
    void viewInvoices();        // Xem hóa đơn hàng tháng
    void makePayment();         // Thanh toán hóa đơn
    void viewPaymentHistory();  // Xem lịch sử thanh toán
    void registerRoom();        // Đăng ký phòng
    void requestService();      // Yêu cầu dịch vụ
};

#endif

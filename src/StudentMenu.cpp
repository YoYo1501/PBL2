#include "../include/models/Contract.h"
#include "../include/models/Payment.h"
#include "../include/models/Room.h"
#include "../include/Graphics.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/StudentMenu.h"
#include <iostream>
#include <ctime>
using namespace std;

void StudentMenu::show() {
    int choice;
    do {
        Graphics::showStudentHeader();
        Graphics::showMenuHeader("MENU SINH VIEN");
        
        Graphics::showMenuOption(1, "Xem thong tin ca nhan");
        Graphics::showMenuOption(2, "Chinh sua thong tin ca nhan");
        Graphics::showMenuOption(3, "Xem lich su hop dong");
        Graphics::showMenuOption(4, "Xem hoa don hang thang");
        Graphics::showMenuOption(5, "Thanh toan hoa don");
        Graphics::showMenuOption(6, "Xem lich su thanh toan");
        Graphics::showMenuOption(7, "Dang ky phong");
        Graphics::showMenuOption(8, "Yeu cau dich vu");
        Graphics::showMenuSeparator();
        Graphics::showMenuOption(0, "Dang xuat");
        
        Graphics::showMenuFooter();
        
        Graphics::setColor(YELLOW, BLACK);
        cout << "    >> Lua chon cua ban: ";
        Graphics::setColor(WHITE, BLACK);
        cin >> choice;
        Graphics::resetColor();

        switch (choice) {
        case 1:
            Graphics::showLoadingBar("Dang tai thong tin ca nhan", 500);
            currentUser.viewProfile();
            Graphics::pauseWithMessage();
            break;
        case 2:
            cin.ignore();
            Graphics::showInfoMessage("Che do chinh sua thong tin");
            currentUser.editProfile();
            authSystem.saveUsersToFile();
            Graphics::pauseWithMessage();
            break;
        case 3:
            Graphics::showLoadingBar("Dang tai lich su hop dong", 500);
            viewContractHistory();
            Graphics::pauseWithMessage();
            break;
        case 4:
            Graphics::showLoadingBar("Dang tai hoa don", 500);
            viewInvoices();
            break;
        case 5:
            Graphics::showLoadingBar("Dang tai thong tin thanh toan", 500);
            makePayment();
            break;
        case 6:
            Graphics::showLoadingBar("Dang tai lich su thanh toan", 500);
            viewPaymentHistory();
            Graphics::pauseWithMessage();
            break;
        case 7:
            Graphics::showLoadingBar("Dang tai danh sach phong", 500);
            registerRoom();
            break;
        case 8:
            cin.ignore();
            Graphics::showInfoMessage("Gui yeu cau dich vu");
            requestService();
            break;
        case 0:
            Graphics::showSuccessMessage("Dang xuat thanh cong!");
            Graphics::showLoadingBar("Dang quay ve menu chinh", 500);
            break;
        default:
            Graphics::showErrorMessage("Lua chon khong hop le!");
            Graphics::pauseWithMessage();
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

void StudentMenu::viewInvoices() {
    vector<Payment> payments = Payment::getPaymentsByStudent(currentUser.getStudentId());
    
    if (payments.empty()) {
        cout << "\n>> Khong co hoa don nao!\n";
        return;
    }
    
    cout << "\n===== DANH SACH HOA DON =====\n";
    for (size_t i = 0; i < payments.size(); ++i) {
        cout << (i + 1) << ". Thang " << payments[i].getMonth() 
             << " - " << payments[i].getTotalAmount() << " VND"
             << " - " << payments[i].getStatus() << endl;
    }
    
    cout << "\nNhap so thu tu de xem chi tiet (0 de quay lai): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)payments.size()) {
        payments[choice - 1].displayInvoice();
        cout << "\nNhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
    }
}

void StudentMenu::makePayment() {
    vector<Payment> unpaidPayments = Payment::getUnpaidPaymentsByStudent(currentUser.getStudentId());
    
    if (unpaidPayments.empty()) {
        cout << "\n>> Khong co hoa don nao can thanh toan!\n";
        return;
    }
    
    cout << "\n===== HOA DON CHUA THANH TOAN =====\n";
    for (size_t i = 0; i < unpaidPayments.size(); ++i) {
        cout << (i + 1) << ". Thang " << unpaidPayments[i].getMonth() 
             << " - " << unpaidPayments[i].getTotalAmount() << " VND" << endl;
    }
    
    cout << "\nChon hoa don de thanh toan (0 de quay lai): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)unpaidPayments.size()) {
        Payment& selectedPayment = unpaidPayments[choice - 1];
        selectedPayment.displayInvoice();
        
        cout << "\nXac nhan thanh toan? (1: Co, 0: Khong): ";
        int confirm;
        cin >> confirm;
        
        if (confirm == 1) {
            selectedPayment.markAsPaid();
            if (Payment::updatePaymentInFile(selectedPayment)) {
                cout << "\n>> Thanh toan thanh cong!\n";
                cout << ">> Cam on ban da thanh toan dung han!\n";
            } else {
                cout << "\n>> Loi khi cap nhat file!\n";
            }
        }
    }
}

void StudentMenu::viewPaymentHistory() {
    vector<Payment> payments = Payment::getPaymentsByStudent(currentUser.getStudentId());
    vector<Payment> paidPayments;
    
    for (const auto& payment : payments) {
        if (payment.getStatus() == "paid") {
            paidPayments.push_back(payment);
        }
    }
    
    if (paidPayments.empty()) {
        cout << "\n>> Chua co lich su thanh toan!\n";
        return;
    }
    
    cout << "\n===== LICH SU THANH TOAN =====\n";
    double totalPaid = 0;
    for (const auto& payment : paidPayments) {
        cout << "Thang " << payment.getMonth() 
             << " - " << payment.getTotalAmount() << " VND"
             << " - Ngay TT: " << payment.getPaymentDate() << endl;
        totalPaid += payment.getTotalAmount();
    }
    cout << "----------------------------\n";
    cout << "Tong da thanh toan: " << totalPaid << " VND\n";
    cout << "==============================\n";
}

void StudentMenu::registerRoom() {
    // Kiểm tra xem sinh viên đã có phòng chưa
    vector<Contract> currentContracts;
    ifstream contractFile("data/contracts.txt");
    string line;
    
    while (getline(contractFile, line)) {
        if (!line.empty()) {
            Contract c = Contract::fromString(line);
            if (c.studentId == currentUser.getStudentId() && c.status == "active") {
                currentContracts.push_back(c);
            }
        }
    }
    contractFile.close();
    
    if (!currentContracts.empty()) {
        cout << "\n>> Ban da co phong: " << currentContracts[0].roomId << endl;
        cout << ">> Vui long tra phong truoc khi dang ky phong moi!\n";
        return;
    }
    
    // Hiển thị danh sách phòng trống
    vector<Room> availableRooms = Room::getAvailableRooms();
    
    if (availableRooms.empty()) {
        cout << "\n>> Hien tai khong co phong trong!\n";
        return;
    }
    
    cout << "\n===== DANH SACH PHONG TRONG =====\n";
    for (size_t i = 0; i < availableRooms.size(); ++i) {
        const Room& room = availableRooms[i];
        cout << (i + 1) << ". " << room.getRoomId() 
             << " - " << room.getBuilding() << " - Tang " << room.getFloor()
             << " - " << room.getRoomType() 
             << " - " << room.getMonthlyRent() << " VND/thang"
             << " - Con trong: " << (room.getCapacity() - room.getCurrentOccupants()) << " cho" << endl;
    }
    
    cout << "\nChon phong de dang ky (0 de quay lai): ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= (int)availableRooms.size()) {
        Room selectedRoom = availableRooms[choice - 1];
        selectedRoom.displayRoomInfo();
        
        cout << "\nXac nhan dang ky phong nay? (1: Co, 0: Khong): ";
        int confirm;
        cin >> confirm;
        
        if (confirm == 1) {
            // Tạo contract mới
            string contractId = "CT" + currentUser.getStudentId() + "_" + selectedRoom.getRoomId();
            string startDate = "01/10/2025"; // Simplified
            string endDate = "01/10/2026";   // 1 year contract
            
            Contract newContract;
            newContract.contractId = contractId;
            newContract.studentId = currentUser.getStudentId();
            newContract.roomId = selectedRoom.getRoomId();
            newContract.startDate = startDate;
            newContract.endDate = endDate;
            newContract.status = "active";
            
            // Lưu contract
            ofstream contractOutFile("data/contracts.txt", ios::app);
            if (contractOutFile.is_open()) {
                contractOutFile << newContract.toString() << endl;
                contractOutFile.close();
                
                // Cập nhật room occupancy
                selectedRoom.addOccupant();
                Room::updateRoomInFile(selectedRoom);
                
                cout << "\n>> Dang ky phong thanh cong!\n";
                cout << ">> Ma hop dong: " << contractId << endl;
                cout << ">> Thoi han: " << startDate << " den " << endDate << endl;
            } else {
                cout << "\n>> Loi khi luu hop dong!\n";
            }
        }
    }
}

void StudentMenu::requestService() {
    cout << "\n===== YEU CAU DICH VU =====\n";
    cout << "1. Sua chua dien\n";
    cout << "2. Sua chua nuoc\n";
    cout << "3. Sua chua internet\n";
    cout << "4. Bao tri phong\n";
    cout << "5. Khac\n";
    cout << "Chon loai yeu cau: ";
    
    int serviceType;
    cin >> serviceType;
    cin.ignore(); // Clear buffer
    
    string serviceTypeStr;
    switch (serviceType) {
        case 1: serviceTypeStr = "Sua chua dien"; break;
        case 2: serviceTypeStr = "Sua chua nuoc"; break;
        case 3: serviceTypeStr = "Sua chua internet"; break;
        case 4: serviceTypeStr = "Bao tri phong"; break;
        case 5: serviceTypeStr = "Khac"; break;
        default:
            cout << ">> Lua chon khong hop le!\n";
            return;
    }
    
    string description;
    cout << "Mo ta chi tiet van de: ";
    getline(cin, description);
    
    if (description.empty()) {
        cout << ">> Mo ta khong duoc de trong!\n";
        return;
    }
    
    string urgency;
    cout << "Muc do khan cap (Thap/Trung binh/Cao): ";
    getline(cin, urgency);
    
    // Tạo ID yêu cầu
    string requestId = "REQ" + currentUser.getStudentId() + "_" + to_string(time(0));
    string requestDate = "20/09/2025"; // Simplified
    string status = "pending";
    
    // Lưu vào file
    ofstream serviceFile("data/service_requests.txt", ios::app);
    if (serviceFile.is_open()) {
        serviceFile << requestId << "|" << currentUser.getStudentId() << "|" 
                   << serviceTypeStr << "|" << description << "|" 
                   << urgency << "|" << requestDate << "|" << status << endl;
        serviceFile.close();
        
        cout << "\n>> Gui yeu cau thanh cong!\n";
        cout << ">> Ma yeu cau: " << requestId << endl;
        cout << ">> Bo phan ky thuat se lien he trong 24h!\n";
    } else {
        cout << "\n>> Loi khi gui yeu cau!\n";
    }
}


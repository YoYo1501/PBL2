#include "../../include/models/User.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

User::User() : username(""), password(""), role(""), fullname(""),
               studentId(""), dob(""), address(""), phone(""), email("") {}

User::User(string uname, string pwd, string r, string fname,
           string sid, string d, string addr, string p, string e)
    : username(uname), password(pwd), role(r), fullname(fname),
      studentId(sid), dob(d), address(addr), phone(p), email(e) {}

// Getter
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getRole() const { return role; }
string User::getFullName() const { return fullname; }
string User::getStudentId() const { return studentId; }
string User::getDob() const { return dob; }
string User::getAddress() const { return address; }
string User::getPhone() const { return phone; }
string User::getEmail() const { return email; }

// Setter
void User::setPassword(string pwd) { password = pwd; }
void User::setRole(string r) { role = r; }
void User::setFullName(string fname) { fullname = fname; }
void User::setStudentId(string sid) { studentId = sid; }
void User::setDob(string d) { dob = d; }
void User::setAddress(string a) { address = a; }
void User::setPhone(string p) { phone = p; }
void User::setEmail(string e) { email = e; }

// Chuyển thành chuỗi để lưu file
string User::toString() const {
    return username + "|" + password + "|" + role + "|" + fullname + "|" +
           studentId + "|" + dob + "|" + address + "|" + phone + "|" + email;
}

// Tạo User từ chuỗi trong file
User User::fromString(string data) {
    vector<string> tokens;
    string token;
    istringstream ss(data);

    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    while (tokens.size() < 9) tokens.push_back("");

    return User(tokens[0], tokens[1], tokens[2], tokens[3],
                tokens[4], tokens[5], tokens[6], tokens[7], tokens[8]);
}

// Xem hồ sơ
void User::viewProfile() const {
    // Đọc thông tin chi tiết từ file information.txt nếu là sinh viên
    std::string mssv = studentId;
    std::string infoFile = "data/information.txt";
    std::ifstream fin(infoFile);
    std::string line;
    std::vector<std::string> fields(12, "Chua cap nhat");
    bool found = false;
    if (fin.is_open()) {
        while (getline(fin, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            while (getline(iss, token, '|')) tokens.push_back(token);
            if (!tokens.empty() && tokens[0] == mssv) {
                // Đảm bảo có đủ 12 trường
                while (tokens.size() < 12) tokens.push_back("Chua cap nhat");
                for (size_t i = 0; i < 12; ++i) fields[i] = tokens[i];
                found = true;
                break;
            }
        }
        fin.close();
    }
    cout << "\n===== THONG TIN CA NHAN =====\n";
    cout << "MSSV        : " << fields[0] << endl;
    cout << "Ho ten      : " << fields[1] << endl;
    cout << "Gioi tinh   : " << fields[2] << endl;
    cout << "Que quan    : " << fields[3] << endl;
    cout << "Ngay sinh   : " << fields[4] << endl;
    cout << "Lop         : " << fields[5] << endl;
    cout << "Nganh       : " << fields[6] << endl;
    cout << "So dien thoai: " << fields[7] << endl;
    cout << "Email       : " << fields[8] << endl;
    cout << "Dia chi hien tai: " << fields[9] << endl;
    cout << "Ngan hang   : " << fields[10] << endl;
    cout << "So TK       : " << fields[11] << endl;
    cout << "=============================\n";
}


// Chỉnh sửa hồ sơ
void User::editProfile() {
    cout << "\n===== CHINH SUA THONG TIN CA NHAN =====\n";
    
    // Đọc thông tin hiện tại từ file information.txt
    std::string mssv = studentId;
    std::string infoFile = "data/information.txt";
    std::vector<std::string> allLines;
    std::vector<std::string> currentInfo(12, "");
    bool found = false;
    
    // Đọc tất cả dữ liệu
    std::ifstream fin(infoFile);
    std::string line;
    while (getline(fin, line)) {
        allLines.push_back(line);
        if (!found) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            while (getline(iss, token, '|')) tokens.push_back(token);
            if (!tokens.empty() && tokens[0] == mssv) {
                while (tokens.size() < 12) tokens.push_back("");
                currentInfo = tokens;
                found = true;
            }
        }
    }
    fin.close();
    
    // Cho phép chỉnh sửa
    string input;
    cout << "Ho ten hien tai: " << currentInfo[1] << endl;
    cout << "Ho ten moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[1] = input;
        fullname = input; // Cập nhật trong User object
    }

    cout << "Ngay sinh hien tai: " << currentInfo[4] << endl;
    cout << "Ngay sinh moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[4] = input;
        dob = input;
    }

    cout << "Que quan hien tai: " << currentInfo[3] << endl;
    cout << "Que quan moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[3] = input;
    }

    cout << "So dien thoai hien tai: " << currentInfo[7] << endl;
    cout << "So dien thoai moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[7] = input;
        phone = input;
    }

    cout << "Email hien tai: " << currentInfo[8] << endl;
    cout << "Email moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[8] = input;
        email = input;
    }

    cout << "Dia chi hien tai: " << currentInfo[9] << endl;
    cout << "Dia chi moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[9] = input;
        address = input;
    }

    cout << "Ten ngan hang hien tai: " << currentInfo[10] << endl;
    cout << "Ten ngan hang moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[10] = input;
    }

    cout << "So tai khoan hien tai: " << currentInfo[11] << endl;
    cout << "So tai khoan moi (Enter de bo qua): ";
    getline(cin, input); 
    if (!input.empty()) {
        currentInfo[11] = input;
    }

    // Ghi lại file với thông tin đã cập nhật
    std::ofstream fout(infoFile);
    if (fout.is_open()) {
        for (const auto& fileLine : allLines) {
            std::istringstream iss(fileLine);
            std::string token;
            std::vector<std::string> tokens;
            while (getline(iss, token, '|')) tokens.push_back(token);
            
            if (!tokens.empty() && tokens[0] == mssv) {
                // Ghi dòng đã cập nhật
                fout << currentInfo[0]; // MSSV
                for (size_t i = 1; i < 12; ++i) {
                    fout << "|" << currentInfo[i];
                }
                fout << std::endl;
            } else {
                // Ghi dòng gốc
                fout << fileLine << std::endl;
            }
        }
        fout.close();
        cout << "\n>> Cap nhat thong tin thanh cong!\n";
    } else {
        cout << "\n>> Loi khi cap nhat file!\n";
    }

    cout << ">> Cap nhat thong tin thanh cong!\n";
}

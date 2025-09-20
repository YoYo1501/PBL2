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
                for (size_t i = 0; i < tokens.size() && i < fields.size(); ++i) fields[i] = tokens[i];
                found = true;
                break;
            }
        }
        fin.close();
    }
    cout << "\n===== THONG TIN CA NHAN =====\n";
    cout << "Ho ten      : " << fields[1] << endl;
    cout << "MSSV        : " << fields[0] << endl;
    cout << "Ngay sinh   : " << fields[4] << endl;
    cout << "Dia chi     : " << fields[9] << endl;
    cout << "So dien thoai: " << fields[7] << endl;
    cout << "Email       : " << fields[10] << endl;
    cout << "=============================\n";
}

// Chỉnh sửa hồ sơ
void User::editProfile() {
    cout << "\n===== CHINH SUA THONG TIN CA NHAN =====\n";
    string input;

    cin.ignore();
    cout << "Ho ten moi (Enter de bo qua): ";
    getline(cin, input); if (!input.empty()) fullname = input;

    cout << "Ngay sinh moi (Enter de bo qua): ";
    getline(cin, input); if (!input.empty()) dob = input;

    cout << "Dia chi moi (Enter de bo qua): ";
    getline(cin, input); if (!input.empty()) address = input;

    cout << "So dien thoai moi (Enter de bo qua): ";
    getline(cin, input); if (!input.empty()) phone = input;

    cout << "Email moi (Enter de bo qua): ";
    getline(cin, input); if (!input.empty()) email = input;

    cout << ">> Cap nhat thong tin thanh cong!\n";
}

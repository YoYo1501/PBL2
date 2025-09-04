#include "../../include/models/user.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;


User::User() : username(""), password(""), role(""), fullname(""), studentId(""), dob(""), address(""), phone(""), email("") {}
User::User(string uname, string pwd, string r, string fname, string sid, string dob, string address, string phone, string email)
    : username(uname), password(pwd), role(r), fullname(fname), studentId(sid), dob(dob), address(address), phone(phone), email(email) {}
string User::getDob() const { return dob; }
string User::getAddress() const { return address; }
string User::getPhone() const { return phone; }
string User::getEmail() const { return email; }

void User::setDob(string d) { dob = d; }
void User::setAddress(string a) { address = a; }
void User::setPhone(string p) { phone = p; }
void User::setEmail(string e) { email = e; }

string User::getUsername() const{
    return username;
}
string User::getPassword() const
{
    return password;
}
string User::getRole() const
{
    return role;
}

string User::getFullName() const
{
    return fullname;
}
string User::getStudentId() const{
    return studentId;
}

void User::setPassword(string pwd){
    password = pwd;
}
void User::setRole(string r){
    role= r;
}
void User::setFullName(string fname){
    fullname = fname;
}
void User::setStudentId(string sid){
    studentId = sid;
}

string User::toString() const {
    return username + "," + password + "," + role + "," + fullname + "," + studentId + "," + dob + "," + address + "," + phone + "," + email;
}

User User::fromString(string data){
    vector<string> tokens;
    string token;
    istringstream ss(data);
    while(getline(ss, token, ',')){
        tokens.push_back(token);
    }
    while(tokens.size() < 9) tokens.push_back("");
    return User(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7], tokens[8]);
}

void User::viewProfile() const {
    using std::cout; using std::endl;
    cout << "===== THÔNG TIN CÁ NHÂN =====" << endl;
    cout << "Họ tên: " << fullname << endl;
    cout << "MSSV: " << studentId << endl;
    cout << "Ngày sinh: " << dob << endl;
    cout << "Địa chỉ: " << address << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Email: " << email << endl;
    cout << "==============================" << endl;
}

void User::editProfile() {
    using std::cout; using std::cin; using std::getline; using std::string;
    cout << "===== CHỈNH SỬA THÔNG TIN CÁ NHÂN =====" << std::endl;
    cout << "Họ tên hiện tại: " << fullname << "\nNhập họ tên mới (Enter để bỏ qua): ";
    string input; getline(cin, input); if(!input.empty()) fullname = input;
    cout << "Ngày sinh hiện tại: " << dob << "\nNhập ngày sinh mới (Enter để bỏ qua): ";
    getline(cin, input); if(!input.empty()) dob = input;
    cout << "Địa chỉ hiện tại: " << address << "\nNhập địa chỉ mới (Enter để bỏ qua): ";
    getline(cin, input); if(!input.empty()) address = input;
    cout << "Số điện thoại hiện tại: " << phone << "\nNhập số điện thoại mới (Enter để bỏ qua): ";
    getline(cin, input); if(!input.empty()) phone = input;
    cout << "Email hiện tại: " << email << "\nNhập email mới (Enter để bỏ qua): ";
    getline(cin, input); if(!input.empty()) email = input;
    cout << "===== ĐÃ CẬP NHẬT THÔNG TIN =====" << std::endl;
}

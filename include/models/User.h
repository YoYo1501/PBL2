#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string role;
    std::string fullname;
    std::string studentId;
    std::string dob;         
    std::string address;
    std::string phone;       
    std::string email;       

public:
    User();
    User(std::string uname, std::string pwd, std::string r, std::string fname,
         std::string sid = "", std::string dob = "", std::string address = "",
         std::string phone = "", std::string email = "");

    // Getter
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;
    std::string getFullName() const;
    std::string getStudentId() const;
    std::string getDob() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::string getEmail() const;

    // Setter
    void setPassword(std::string pwd);
    void setRole(std::string r);
    void setFullName(std::string fname);
    void setStudentId(std::string sid);
    void setDob(std::string d);
    void setAddress(std::string a);
    void setPhone(std::string p);
    void setEmail(std::string e);

    // File I/O
    std::string toString() const;
    static User fromString(std::string data);

    // Actions
    void viewProfile() const;
    void editProfile();
};

#endif

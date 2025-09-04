#ifndef USER_H
#define USER_H

#include <string>


class User{
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
    User(std::string uname, std::string pwd, std::string r, std::string fname, std::string sid =" ",
         std::string dob = "", std::string address = "", std::string phone = "", std::string email = "");

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;
    std::string getFullName() const;
    std::string getStudentId() const;
    std::string getDob() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setPassword(std::string pwd);
    void setRole(std::string r);
    void setFullName(std::string fname);
    void setStudentId(std::string sid);
    void setDob(std::string dob);
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setEmail(std::string email);

    std::string toString() const;
    static User fromString(std::string data);

    void viewProfile() const;
    void editProfile();
};


#endif
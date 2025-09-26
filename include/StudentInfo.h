#ifndef STUDENTINFO_H
#define STUDENTINFO_H
#include <string>

struct StudentInfo
{
    std::string studentId;
    std::string fullName;
    std::string gender;
    std::string address;
    std::string dob;
    std::string classId;
    std::string major;
    std::string phone;
    std::string bankName;
    std::string bankAccount;
    std::string email;
    std::string addressDetail;

    std::string toString() const
    {
        return studentId + "|" + fullName + "|" + gender + "|" + address + "|" + dob + "|" + classId + "|" + major + "|" + phone + "|" + email + "|" + addressDetail + "|" + bankName + "|" + bankAccount;
    }
};

#endif

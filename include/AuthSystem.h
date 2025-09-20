#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include "models/User.h"
#include <vector>
#include <string>

class AuthSystem
{

private:
    std::vector<User> users;
    User *currentUser;
    std::string dataFile;

    void loadUsersFromFile();
    std::string hashPassword(std::string password);

public:
    AuthSystem(std::string filename = "data/accounts.txt");
    ~AuthSystem();

    bool login(std::string username, std::string password);
    bool registerUser(std::string username, std::string password,
                      std::string role, std::string fullName,
                      std::string studentId = "");

    void logout();
    User &getCurrentUser();             
    const User &getCurrentUser() const; 

    bool isLoggedIn() const;

    bool hasRole(std::string requiredRole) const;
    bool isAdmin() const;
    bool isStudent() const;

    bool usernameExists(std::string username) const;

    void saveUsersToFile();
};

#endif
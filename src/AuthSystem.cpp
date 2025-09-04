#include "../include/AuthSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

AuthSystem::AuthSystem(string filename) : dataFile(filename), currentUser(nullptr) {
    loadUsersFromFile();
    
    if (users.empty()) {
        users.push_back(User("admin", "admin123", "admin", "Admin System"));
        saveUsersToFile();
        cout << "Da tao tai khoan admin mac dinh: admin/admin123" << endl;
    }
}

AuthSystem::~AuthSystem() {
    delete currentUser;
    saveUsersToFile();
}

void AuthSystem::loadUsersFromFile() {
    ifstream file(dataFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                User user = User::fromString(line);
                if (!user.getUsername().empty()) {
                    users.push_back(user);
                }
            }
        }
        file.close();
    }
}

void AuthSystem::saveUsersToFile() {
    ofstream file(dataFile);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.toString() << endl;
        }
        file.close();
    }
}

string AuthSystem::hashPassword(string password) {
    return password;
}

bool AuthSystem::login(string username, string password) {
    string hashedPassword = hashPassword(password);
    
    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == hashedPassword) {
            currentUser = new User(user);
            return true;
        }
    }
    return false;
}

bool AuthSystem::registerUser(string username, string password,
                             string role, string fullName, string studentId) {
    if (usernameExists(username)) {
        return false;
    }
    
    string hashedPassword = hashPassword(password);
    users.push_back(User(username, hashedPassword, role, fullName, studentId));
    saveUsersToFile();
    return true;
}

void AuthSystem::logout() {
    delete currentUser;
    currentUser = nullptr;
}

User* AuthSystem::getCurrentUser() const {
    return currentUser;
}

bool AuthSystem::isLoggedIn() const {
    return currentUser != nullptr;
}

bool AuthSystem::hasRole(string requiredRole) const {
    return isLoggedIn() && currentUser->getRole() == requiredRole;
}

bool AuthSystem::isAdmin() const { return hasRole("admin"); }
bool AuthSystem::isStudent() const { return hasRole("student"); }

bool AuthSystem::usernameExists(string username) const {
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return true;
        }
    }
    return false;
}
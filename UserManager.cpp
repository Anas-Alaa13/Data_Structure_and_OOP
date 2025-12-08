#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

bool UserManager::login(DataManager& dm, const std::string& username, const std::string& password, std::string& userType) {
    for (const auto& user : dm.users) {
        if (user.Username == username && user.Password == password) {
            if (username == "admin") {
                userType = "admin";
            }
            else {
                userType = "student";
            }
            return true;
        }
    }
    return false;
}

bool UserManager::registerUser(DataManager& dm, int id, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string& username, const std::string& password, const std::string& email) {
    for (const auto& user : dm.users) {
        if (user.Username == username) {
            return false; // Username already exists
        }
    }
    User newUser{ id, firstName, lastName, phoneNumber, username, password, email };
    dm.users.push_back(newUser);
    dm.writeUsers("database.csv"); // حفظ التغييرات
    return true;
}

bool UserManager::forgot(DataManager& dm, const std::string& username, const std::string& phoneNumber, const std::string& newPassword) {
    for (auto& user : dm.users) {
        if (user.Username == username && user.PhoneNumber == phoneNumber) {
            user.Password = newPassword;
            dm.writeUsers("database.csv"); // حفظ التغييرات
            return true;
        }
    }
    return false;
}
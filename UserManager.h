#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "DataManager.h"
#include <string>

class UserManager {
public:
    bool login(DataManager& dm, const std::string& username, const std::string& password, std::string& userType);
    bool registerUser(DataManager& dm, int id, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber, const std::string& username, const std::string& password, const std::string& email);
    bool forgot(DataManager& dm, const std::string& username, const std::string& phoneNumber, const std::string& newPassword);
};

#endif
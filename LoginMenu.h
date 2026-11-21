#ifndef LOGINMENU_H
#define LOGINMENU_H
#include <string>
#include "InputErrorHandling.h"
#include "UserTable.h"

class LoginMenu{
    ErrorHandler e;
    UserTable users;               
    std::string loggedInUser;
    std::string loggedInRole;

    void DisplayOptions();
    bool Login();
    void Register();
    bool IsValidUsername(const std::string& username);
    bool IsValidPassword(const std::string& password);

    public:
        bool run();                
        std::string GetUsername();
        std::string GetRole();
        UserTable& GetUsers();
};

#endif
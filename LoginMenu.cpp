#include "LoginMenu.h"
#include <iostream>
#include <cctype>

void LoginMenu::DisplayOptions(){
    std::cout << "\n====>LOGIN MENU<====\n";
    std::cout << "====>PRESS 1 TO LOGIN!<====\n";
    std::cout << "====>PRESS 2 TO CREATE A NEW ACCOUNT!<====\n";
    std::cout << "====>PRESS 3 TO EXIT!<====\n";
}

bool LoginMenu::IsValidUsername(const std::string& username){
    if(username.length() < 5 || username.length() > 15){
        return false;
    }
    for(char ch : username){
        if(!std::isalnum((unsigned char)ch) && ch != '_'){
            return false;          
        }
    }
    return true;
}

bool LoginMenu::IsValidPassword(const std::string& password){
    if(password.length() < 5 || password.length() > 15){
        return false;
    }
    for(char ch : password){
        if(ch == ',' || ch == ' '){
            return false;
        }
    }
    return true;
}

bool LoginMenu::Login(){
    for(int attempt = 1; attempt <= 3; attempt++){

        std::string username;
        std::string password;
        
        while(true){

        std::cout << "USERNAME: ";
        if(!std::getline(std::cin, username)){
            std::cin.clear();
            std::cout << "INPUT ERROR! PLEASE TRY AGAIN!\n";
            continue;         
        }
        std::cout << "PASSWORD: ";
        if(!std::getline(std::cin, password)){
            std::cin.clear();
            std::cout << "INPUT ERROR! PLEASE TRY AGAIN!\n";
            continue;
        }
        break;
    }
        UserNode* user = users.FindUser(username);
        if(user != nullptr && user->password == password){
            loggedInUser = user->username;
            loggedInRole = user->role;
            std::cout << "LOGIN SUCCESSFUL. WELCOME, " << loggedInUser << "!\n";
            return true;
        }

        std::cout << "WRONG USERNAME OR PASSWORD! ATTEMPT NO. " << attempt << " OF 3.\n";
    }
    return false;                 
}

void LoginMenu::Register(){
    std::string username;
    std::string password;

    while(true){
        std::cout << "CHOOSE A USERNAME!(5-15 LETTERS, DIGITS OR '_' ONLY):";
        if(!std::getline(std::cin,username)){
            std::cin.clear();
            std::cout << "INPUT ERROR! PLEASE TRY AGAIN!\n";
            continue;
        }
        if(username.empty()){
            return;
        }
        if(!IsValidUsername(username)){
            std::cout << "INVALID USERNNAME!PLEASE TRY AGAIN!\n";
            continue;
        }
        if(users.FindUser(username)!=nullptr){
            std::cout << "THAT USERNAME IS ALREADY TAKEN!\n";
        }else{
            break;
        }
    }
    while(true){
        std::cout << "CHOOSE A PASSWORD!(5-15 CHARACTERS,NO SPACES OR COMMAS):";
        if(!std::getline(std::cin, password)){
            std::cin.clear();
            std::cout << "INPUT ERROR! PLEASE TRY AGAIN!\n";
            continue;
        }
        if(password.empty()){
            return;
        }
        if(!IsValidPassword(password)){
            std::cout << "INVALID PASSWORD.PLEASE TRY AGAIN!\n";
        }else{
            break;
        }
    }
        if(users.AddUser(username, password, "Editor")){
            std::cout << "ACCOUNT CREATED!PROCEED TO LOGIN!\n";
        }

}

bool LoginMenu::run(){
    int choice;
    do{
        DisplayOptions();
        choice = e.ErrorCheck(1, 3);

        if(choice == 1){
            if(Login()){
                return true;
            }
            std::cout << "LOGIN FAILED! EXITING!\n";
            return false;
        }else if(choice == 2){
            Register();
        }
    }while(choice != 3 && choice != -1);

    std::cout << "GOODBYE!\n";
    return false;
}

std::string LoginMenu::GetUsername(){
    return loggedInUser;
}

std::string LoginMenu::GetRole(){
    return loggedInRole;
}

UserTable& LoginMenu::GetUsers(){
    return users;
}
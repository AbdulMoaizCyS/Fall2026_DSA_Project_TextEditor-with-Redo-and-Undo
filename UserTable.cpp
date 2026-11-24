#include "UserTable.h"
#include <iostream>
#include <fstream>

const std::string UserTable::FileName = "Users.txt";

UserTable::UserTable(){

    for(int i = 0; i < SIZE; i++){
        buckets[i] = nullptr;
    }

    // Load existing users
    if(!LoadFromFile()){
        std::cout << "No users found. Creating default admin.\n";
        AddUser("admin", "admin123", "Admin");
    }
}


int UserTable::HashFunction(const std::string& username){
    int sum = 0;

    for(char ch : username){
        sum += (unsigned char)ch;
    }

    return sum % SIZE;
}


UserNode* UserTable::FindUser(const std::string& username){
    int index = HashFunction(username);

    UserNode* current = buckets[index];

    while(current != nullptr){

        if(current->username == username){
            return current;
        }

        current = current->next;
    }

    return nullptr;
}


bool UserTable::AddUser(const std::string& username, const std::string& password, const std::string& role){

    if(FindUser(username) != nullptr){
        return false;
    }

    int index = HashFunction(username);

    UserNode* node = new UserNode;

    node->username = username;
    node->password = password;
    node->role = role;

    node->next = buckets[index];
    buckets[index] = node;

    if(!SaveToFile()){
        std::cout << "Could not save Users.txt\n";
    }

    return true;
}


bool UserTable::DeleteUser(const std::string& username){

    int index = HashFunction(username);

    UserNode* current = buckets[index];
    UserNode* previous = nullptr;

    while(current != nullptr){

        if(current->username == username){

            if(previous == nullptr){
                buckets[index] = current->next;
            }else{
                previous->next = current->next;
            }

            delete current;

            if(!SaveToFile()){
                std::cout << "Could not save Users.txt\n";
            }

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}


void UserTable::DisplayAll(){

    for(int i = 0; i < SIZE; i++){

        UserNode* current = buckets[i];

        while(current != nullptr){

            std::cout << "Bucket " << i << ": "
                      << current->username << " ("
                      << current->role << ")\n";

            current = current->next;
        }
    }
}


bool UserTable::SaveToFile(){

    std::ofstream file(FileName);

    if(!file){
        return false;
    }

    for(int i = 0; i < SIZE; i++){

        UserNode* current = buckets[i];

        while(current != nullptr){

            file << current->username << ","
                 << current->password << ","
                 << current->role << "\n";

            current = current->next;
        }
    }

    file.close();

    if(!file){
        return false;
    }

    return true;
}


bool UserTable::LoadFromFile(){

    std::ifstream file(FileName);

    if(!file){
        return false;
    }

    std::string line;

    int loaded = 0;

    while(std::getline(file, line)){

        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);

        if(firstComma == std::string::npos ||
           secondComma == std::string::npos){
            continue;
        }

        std::string username = line.substr(0, firstComma);

        std::string password = line.substr(
            firstComma + 1,
            secondComma - firstComma - 1
        );

        std::string role = line.substr(secondComma + 1);

        int index = HashFunction(username);

        if(FindUser(username) == nullptr){

            UserNode* node = new UserNode;

            node->username = username;
            node->password = password;
            node->role = role;

            node->next = buckets[index];
            buckets[index] = node;

            loaded++;
        }
    }

    file.close();

    return loaded > 0;
}


UserTable::~UserTable(){

    for(int i = 0; i < SIZE; i++){

        UserNode* current = buckets[i];

        while(current != nullptr){

            UserNode* temp = current;

            current = current->next;

            delete temp;
        }
    }
}
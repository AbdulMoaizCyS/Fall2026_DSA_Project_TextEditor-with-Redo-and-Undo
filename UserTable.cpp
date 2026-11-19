#include "UserTable.h"
#include <iostream>

UserTable::UserTable(){
    for(int i = 0; i < SIZE; i++){
        buckets[i] = nullptr;      
    }
}


int UserTable::HashFunction(const std::string& username){
    int sum = 0;
    for(char ch : username){
        sum += int(ch); 
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
            std::cout << "Bucket " << i << ": " << current->username
                      << " (" << current->role << ")\n";
            current = current->next;
        }
    }
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
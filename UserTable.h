#ifndef USERTABLE_H
#define USERTABLE_H
#include <string>

struct UserNode{
    std::string username;
    std::string password;
    std::string role;
    UserNode* next;
};

class UserTable{
    static const int SIZE = 10;
    UserNode* buckets[SIZE];
    static const std::string FileName;

    int HashFunction(const std::string& username);

    public:
        UserTable();
        bool AddUser(const std::string& username, const std::string& password, const std::string& role);
        UserNode* FindUser(const std::string& username);
        bool DeleteUser(const std::string& username);
        void DisplayAll();
        bool SaveToFile();
        bool LoadFromFile();
        ~UserTable();
};

#endif
#ifndef COMMAND_H
#define COMMAND_H
#include <string>
using namespace std;
enum CommandType {insert_cmd,edit_cmd,delete_cmd};
class Command {
    public:
    CommandType type;
    int lineno;
    string oldText;
    string newText;
    Command();
    Command(CommandType t,int line,const string& oldT,const string& newT);
    string typeName() const;
};
#endif
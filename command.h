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
    Command(){
        type = edit_cmd;
        lineno = 0;
        oldText = "";
        newText = "";
    }
    Command(CommandType t,int line,const string& oldT,const string& newT){
        type = t;
        lineno = line;
        oldText = oldT;
        newText = newT;
    }
    string typeName() const{
        if(type == insert_cmd)return "INSERT";
        if(type == edit_cmd)return "EDIT";
        return "DELETE";
    }
};
#endif
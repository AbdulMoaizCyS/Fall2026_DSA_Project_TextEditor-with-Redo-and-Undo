#include "Command.h"
Command::Command(){
    type = edit_cmd;
    lineno = 0;
    oldText = "";
    newText = "";
}
Command::Command(CommandType t,int line,const string& oldT,const string& newT){
    type = t;
    lineno = line;
    oldText = oldT;
    newText = newT;
}
string Command::typeName() const{
    if(type == insert_cmd)return "INSERT";
    if(type == edit_cmd)return "EDIT";
    return "DELETE";
}
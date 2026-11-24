#ifndef BRACKETCHECKER_H
#define BRACKETCHECKER_H

#include "TextBuffer.h"   // Member A (replace with filename)

const int BRACKET_MAX = 1000;

class BracketStack {
    char data[BRACKET_MAX];
    int lineNo[BRACKET_MAX];
    int top;

public:
    BracketStack();
    bool isEmpty();
    bool isFull();
    void push(char c, int line);
    void pop();
    char peek();
    int peekLine();
};

bool bracketsMatch(char open, char close);
int checkBrackets(TEXT_BUFFER& buf);
void runBracketChecker(TEXT_BUFFER& buf);

#endif

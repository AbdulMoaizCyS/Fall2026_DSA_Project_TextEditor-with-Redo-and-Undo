#include "BracketChecker.h"
#include <iostream>
#include <string>

using namespace std;

BracketStack::BracketStack() {
    top = -1;
}

bool BracketStack::isEmpty() {
    return top == -1;
}

bool BracketStack::isFull() {
    return top == BRACKET_MAX - 1;
}

void BracketStack::push(char c, int line) {
    if (!isFull()) {
        top++;
        data[top] = c;
        lineNo[top] = line;
    }
}

void BracketStack::pop() {
    if (!isEmpty()) {
        top--;
    }
}

char BracketStack::peek() {
    return data[top];
}

int BracketStack::peekLine() {
    return lineNo[top];
}

bool bracketsMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// 0 = all good otherwise error line number
int checkBrackets(TEXT_BUFFER& buf) {
    BracketStack s;
    int total = buf.GetTotal();
    for (int i = 1; i <= total; i++) {
        string line = buf.Get_line(i);
        for (char c : line) {
            if (c == '(' || c == '{' || c == '[') {
                s.push(c, i);
            } else if (c == ')' || c == '}' || c == ']') {
                if (s.isEmpty()) return i;
                if (!bracketsMatch(s.peek(), c)) return i;
                s.pop();
            }
        }
    }
    if (!s.isEmpty()) return s.peekLine();
    return 0;
}

void runBracketChecker(TEXT_BUFFER& buf) {
    int result = checkBrackets(buf);
    if (result == 0) {
        cout << "All brackets are balanced." << endl;
    } else {
        cout << "Problem found on line " << result << endl;
    }
}

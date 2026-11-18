#ifndef EXTRAS_H
#define EXTRAS_H

#include <iostream>
#include <string>
#include "TextBuffer.h"   // Member A (replace with filename)
#include "Command.h"      // Member B (unchanged)
using namespace std;

// ===================================================
// F7: BRACKET CHECKER (array-based stack)
// ===================================================
const int BRACKET_MAX = 1000;

class BracketStack {
    char data[BRACKET_MAX];
    int lineNo[BRACKET_MAX];
    int top;
public:
    BracketStack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == BRACKET_MAX - 1; }
    void push(char c, int line) {
        if (!isFull()) { top++; data[top] = c; lineNo[top] = line; }
    }
    void pop()     { if (!isEmpty()) top--; }
    char peek()    { return data[top]; }
    int peekLine() { return lineNo[top]; }
};

inline bool bracketsMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// 0 = all good otherwise error
inline int checkBrackets(TEXT_BUFFER& buf) {
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

inline void runBracketChecker(TEXT_BUFFER& buf) {
    int result = checkBrackets(buf);
    if (result == 0) cout << "All brackets are balanced." << endl;
    else             cout << "Problem found on line " << result << endl;
}

// ===================================================
// F6: MERGE SORT (recursion, undoable)
// ===================================================
inline void mergeParts(string arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    string* L = new string[n1];
    string* R = new string[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

inline void mergeSort(string arr[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    mergeParts(arr, left, mid, right);
}

inline void sortLines(TEXT_BUFFER& buf) {
    int n = buf.GetTotal();
    if (n < 2) {
        cout << "Nothing to sort." << endl;
        return;
    }
    string* arr = new string[n];
    for (int i = 0; i < n; i++) arr[i] = buf.Get_line(i + 1);
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) buf.Edit_line(i + 1, arr[i]);
    delete[] arr;
    cout << "Lines sorted A-Z." << endl;
}

// ===================================================
// Recent files (array-based circular queue, last 5)
// ===================================================
const int RECENT_SIZE = 5;

class RecentFiles {
    string files[RECENT_SIZE];
    int front;
    int count;
public:
    RecentFiles() { front = 0; count = 0; }
    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == RECENT_SIZE; }

    void addFile(string name) {
        if (isFull()) {
            front = (front + 1) % RECENT_SIZE;
            count--;
        }
        int rear = (front + count) % RECENT_SIZE;
        files[rear] = name;
        count++;
    }

    void display() {
        if (isEmpty()) {
            cout << "No recent files." << endl;
            return;
        }
        cout << "Recent files:" << endl;
        for (int i = 0; i < count; i++) {
            int idx = (front + count - 1 - i) % RECENT_SIZE;
            cout << i + 1 << ". " << files[idx] << endl;
        }
    }
};

// ===================================================
// F5: SEARCH AND REPLACE
// ===================================================

inline void findWord(TEXT_BUFFER& buf, const string& word) {
    if (word.empty()) {
        cout << "Please enter a word to search." << endl;
        return;
    }
    int total = buf.GetTotal();
    bool found = false;
    for (int i = 1; i <= total; i++) {
        if (buf.Get_line(i).find(word) != string::npos) {
            cout << "Found on line " << i << endl;
            found = true;
        }
    }
    if (!found) cout << "\"" << word << "\" not found." << endl;
}

// Ek line mein har oldWord ko newWord se badal do
inline string replaceInLine(string line, const string& oldWord, const string& newWord) {
    size_t pos = 0;
    while ((pos = line.find(oldWord, pos)) != string::npos) {
        line.replace(pos, oldWord.length(), newWord);
        pos += newWord.length();   // aage barho, warna infinite loop
    }
    return line;
}

template <class UndoStack>
void replaceAll(TEXT_BUFFER& buf, const string& oldWord, const string& newWord, UndoStack& undo) {
    if (oldWord.empty()) {
        cout << "Please enter a word to replace." << endl;
        return;
    }
    int total = buf.GetTotal();
    int changed = 0;
    for (int i = 1; i <= total; i++) {
        string oldLine = buf.Get_line(i);
        if (oldLine.find(oldWord) == string::npos) continue;

        string newLine = replaceInLine(oldLine, oldWord, newWord);
        buf.Edit_line(i, newLine);
        undo.push(Command(edit_cmd, i, oldLine, newLine));   // <-- match with Member B (pending)
        changed++;
    }
    cout << "Replaced in " << changed << " line(s)." << endl;
}

#endif

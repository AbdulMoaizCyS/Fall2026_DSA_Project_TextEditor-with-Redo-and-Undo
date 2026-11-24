#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>

struct Node {
    std::string line;
    Node* next;
    Node* prev;
};

// Line numbers start from 1.
class TEXT_BUFFER {
    Node* head;
    Node* tail;
    int Totalentries;

public:
    TEXT_BUFFER();
    ~TEXT_BUFFER();

    // no copying (would cause a double delete)
    TEXT_BUFFER(const TEXT_BUFFER&) = delete;
    TEXT_BUFFER& operator=(const TEXT_BUFFER&) = delete;

    // Valid n: 1 to Totalentries + 1
    bool Insert_line_at(int n, const std::string& line);

    // Replaces line, saves the OLD text in oldLine (for undo)
    bool Edit_line(int index, const std::string& newLine, std::string& oldLine);

    // Deletes line, saves the deleted text in oldLine (for undo)
    bool Delete_line(int index, std::string& oldLine);

    bool Get_line(int index, std::string& line);

    void Display();

    int getTotal();
};

#endif

#ifndef MERGESORT_H
#define MERGESORT_H

#include <string>
#include "TextBuffer.h"   // Member A (replace with filename)

void mergeParts(std::string arr[], int left, int mid, int right);
void mergeSort(std::string arr[], int left, int right);
void sortLines(TEXT_BUFFER& buf);

#endif

#include "MergeSort.h"
#include <iostream>
#include <string>

using namespace std;

void mergeParts(string arr[], int left, int mid, int right) {
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

void mergeSort(string arr[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    mergeParts(arr, left, mid, right);
}

void sortLines(TEXT_BUFFER& buf) {
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

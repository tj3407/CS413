#include <iostream>
using namespace std;

bool isMaxHeap(int atree[], int size) {
    if (size <= 1) return true;
    int n = 0;

    while (n < (size/2)) {
        int parent = atree[n];  // <= parent node
        int left = atree[2*n +1]; // <= left Child
        int right = atree[2*n +2]; // <= right Child

        if (parent < left || parent < right) {
            return false;
        }

        n++;
    }

    return true;
}

int main() {
    int SIZE = 9;
    int arr[] = { 10, 8, 7, 5, 4, 3, 2, 1, 0 };
    string result;

    if (isMaxHeap(arr, SIZE)) {
        result = "true";
    } else {
        result = "false";
    }

    cout << "isMaxHeap: " << result << endl;
}
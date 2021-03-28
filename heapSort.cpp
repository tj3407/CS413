#include <iostream>
using namespace std;

void fixheap(int a[], int left, int right) {
     int x;
     x = a[left];
     int i ,j;

     for (i = left, j = 2*i + 1; j <= right; i = j, j = 2*i + 1) {
          if (j < right && a[j+1] > a[j])   j++;
          if (x >= a[j]) break;
          a[i] = a[j];
     }

     a[i] =  x;
}

void heapSort(int a[], int n) {
     if (n > 1) {
          // start of phase 1
          for (int left = n/2-1; left >= 0; left--) {
               fixheap(a,left,n-1);
               for (int i = 0; i < n ; i++) {
                    cout << "end of fixheap: ";
                    cout << a[i] << endl;
               }
          }

           // end of phase 1

          // start of phase 2
          swap(a[0], a[n-1]);

          for (int right = n-2;  right >= 1; right--) {
          fixheap(a,0,right);
          swap(a[0], a[right]);
          }
          // end of phase 2
     }

}

int main() {
    int size = 9;
    int arrnum[] = {0,1,6,8,4,3,5,2,7};
    heapSort(arrnum, size);
}
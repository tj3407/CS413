#include <iostream>
using namespace std;
int counter;

int getAverage(int min, int max, int left, int right) {
    int avg = floor((min+max)/2);
    return avg;
}

void fill( int b [], int length ) {
    if (length < 2) b[0] = 0;
    int avg = getAverage(0, length-1, 0, length-1);
}
 
int partition( int a [], int low , int high ) {
    int x = a [ low ];
    bool highTurn = true ;
    while ( low < high ) {
        counter++;  // to count item comparisons
        if (highTurn)
            if ( a [ high ] >= x) high --;
            else {
                a [ low ++] = a [ high ];
                highTurn = false ;
            }
        else
            if ( a [ low ] <= x) low ++;
            else {
                a [ high --] = a [ low ];
                highTurn = true ;
            }
    }
    a [ low ] = x;
    return low ;
}
void quicksort1( int a [], int start , int end ) {
    if ( start >= end ) return ;
    int mid = partition( a , start , end );
    quicksort1( a , start , mid - 1);
    quicksort1( a , mid + 1, end );
}
void quicksort( int a [], int length ) {
    quicksort1( a , 0, length - 1);
}
void test( int array [], int length ) {
    counter = 0;
    quicksort( array , length );
    cout << "For length = " << length << ", counter = " << counter << endl;
}
 
 
int main() {
    int * buffer;
    buffer = new int [4194304] ;
    int n = 1;
    while (n <= 4194304) {
            fill(buffer, n);
            test(buffer, n);
            n = 2 * n + 1;
    }
    delete[] buffer;
    return 0;
}
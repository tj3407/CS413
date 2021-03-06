#include <iostream>
using namespace std;
int counter;
int partition( int a [], int low , int high ) {
      int   x = a [ low ];      
      bool highTurn = true ;
      while ( low < high ) {
            counter++;  // to count item comparisons highlighted in green
            if (highTurn)
                  if ( a [ high ] >= x ) high --;
                  else {
                        a [ low ++] = a [ high ];
                        highTurn = false ;
                  }
            else
                  if ( a [ low ] <= x ) low ++;
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
      // Array contents for a1, a2, a3 give best case counts for their respective sizes.
      int    a1[] = { 0 },                      // Array size 2^1 - 1
            a2[] = { 1, 0, 2 },                // Array size 2^2 - 1
            a3[] = { 3, 0, 2, 1, 5, 4, 6 },     // Array size 2^3 – 1
 
            // Edit the line below so that a4 gives a best case count.  Reorder the original values 0, 1, ..., 13, 14.
            a4[] = { 7, 0, 2, 1, 5, 4, 6, 3, 11, 8, 10, 9, 13, 12, 14 }; // Array size 2^4 – 1
 
      test(a1, 1);
      test(a2, 3);
      test(a3, 7);
      test(a4, 15);
 
      return 0;
}
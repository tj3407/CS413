/*

Determine the runtimes for various sorting functions.
*/

#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

const int MAXSIZE = 30000000;  // you might need to set this to a lower value
const int DATASIZE = 1;  // a bigger value will emphasize the cost of assignments vs. comparisons
int counter;
struct record {
    long long int key;
    // char value[DATASIZE];
};

record 	buf1[MAXSIZE],  // orig. list of random numbers
buf2[MAXSIZE];  // copy of the numbers to pass to sortX

void sort0(record  nums[], int len);  // slowsort
void sort1(record  nums[], int len);  // "optimized" slowsort
void sort2(record  nums[], int len);  // bubblesort
void sort3(record  nums[], int len);  // optimized bubblesort
void sort4(record  nums[], int len);  // selection sort
void sort5(record  nums[], int len);  // insertion sort
void sort6(record  nums[], int len);  // mergesort
void sort7(record  nums[], int len);  // quicksort
void sort8(record  nums[], int len);  // opt quicksort
void sort9(record  nums[], int len);  // heapsort
void sort10(record nums[], int len);  // radixsort

void print(record  nums[], int len, bool newLine);
void fill(record   nums[], int len, char orderCode);
void copyTo(record from[], record to[], int len);
double timeIt(void(*sort)(record[], int), int len, int loops, bool printIt, int ocode);

string sortNames[] = {
"reg. slowsort",
"opt. slowsort",
"bubblesort",
"opt.bubblesort",
"selection sort",
"insertion sort",
"mergesort",
"quicksort",
"opt.quicksort",
"heapsort",
"radixsort" };


int main()
{

    srand((unsigned int)time(0));
    void(*sorts[]) (record[], int) = { sort0, sort1, sort2, sort3, sort4, sort5, sort6, sort7, sort8, sort9, sort10 };
    int numSorts = 11, startId, endId, loops;
    char response, ocode;
    bool printIt;
    for (int i = 0; i < numSorts; i++) {
        cout << i << ": " << sortNames[i] << endl;
    }
    cout << "What is the start ID ? ";
    cin >> startId;
    startId = max(0, startId);
    cout << "What is the end ID ? ";
    cin >> endId;
    endId = min(numSorts - 1, endId);
    cout << "Ascending, shuffled, descending or random ('a','s','d','r') ? ";
    cin >> ocode;

    cout << "Print the arrays (y/n) ? ";
    cin >> response;
    printIt = response == 'y';
    cout << "How many calls per test? ";
    cin >> loops;
    loops = max(1, loops);
    cout << setprecision(5) << endl;
    bool done = false;
    while (!done) {
        int size;
        cout << "What is the array size (0 to quit)? ";
        cin >> size;
        if (size <= 0) done = true;
        else {

            if (size > MAXSIZE) {
                cout << "Too big...setting size to " << MAXSIZE << "." << endl;
                size = MAXSIZE;
            }

            for (int i = startId; i <= endId; i++) {
                cout << "Starting sort" << i << "( " << sortNames[i] << " ) ... " << flush;
                counter = 0;
                double time = timeIt(*sorts[i], size, loops, printIt, ocode);
              //  cout << counter << endl;
                cout << "done. Time" << i << " = " << time << "ms ";
                if (loops > 1) cout << " = \t" << time / loops << "ms per call ";
                cout << endl << endl;
            }
        }
    }
    return 0;

}


//  slowsort
void sort0(record  nums[], int len) {
    if (len <= 1) return;
    sort0(nums + 1, len - 1);
    if (nums[0].key > nums[1].key)
        swap(nums[0], nums[1]);
    sort0(nums + 1, len - 1);
}

// optimized slowsort (avoids needless recursive call)
void sort1(record  nums[], int len) {
    if (len <= 1) return;
    sort1(nums + 1, len - 1);
   // counter++;
    if (nums[0].key > nums[1].key) {
        swap(nums[0], nums[1]);
        sort1(nums + 1, len - 1);
    }
}

// bubble sort
void sort2(record  nums[], int len) {
    for (int i = len - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (nums[j].key > nums[j + 1].key) {
                //record temp = nums[j];
                //nums[j] = nums[j+1];
                //nums[j+1] = temp;
                swap(nums[j], nums[j + 1]);
            }
}


// bubble sort, slightly optimized
void sort3(record  nums[], int len) {
    for (int i = len - 1; i > 0; i--) {
        bool didSwap = false;
        for (int j = 0; j < i; j++)
            if (nums[j].key > nums[j + 1].key) {
                swap(nums[j], nums[j + 1]);
                didSwap = true;
            }
        if (!didSwap) return;
    }
}


// selection sort (this is a minsort)
void sort4(record  nums[], int len) {
    for (int start = 0; start < len; start++) {
        int minIndex = start;
        for (int i = start + 1; i < len; i++)
            if (nums[minIndex].key > nums[i].key)
                minIndex = i;
        swap(nums[start], nums[minIndex]);
    }
}


// insertion sort
void sort5(record nums[], int length) {
    for (int i = 1; i < length; i++) {
        record toInsert = nums[i];
        int j;
        for (j = i; j > 0 && nums[j - 1].key > toInsert.key; j--)
            nums[j] = nums[j - 1];
        nums[j] = toInsert;
    }
}

// helper for mergeSort1
record* merge(record* p1, int length1, record* p2, int length2, record* buff) {
    for (int i = 0, j = 0, k = 0; k < length1 + length2;) {
        if (i < length1 && (j >= length2 || p1[i].key < p2[j].key))
            buff[k++] = p1[i++];
        if (j < length2 && (i >= length1 || p2[j].key <= p1[i].key))
            buff[k++] = p2[j++];
    }
    return buff;
}

// helper for sort6 (mergesort)
void mergeSort1(record* first, record* last, record* buff) {
    if (first >= last) return;
    int length = last - first + 1, len1 = length / 2;
    mergeSort1(first, first + len1 - 1, buff);
    mergeSort1(first + len1, last, buff);
    merge(first, len1, first + len1, length - len1, buff);

    while (first <= last)
        *first++ = *buff++;  // copy back to original array
}


// mergesort
void sort6(record nums[], int length) {
    record* buff = new record[length];  // O(n) extra memory 
    mergeSort1(nums, nums + length - 1, buff);
    delete[] buff;
}

int findPivot(record a[], int low, int high) {
    int indexOfMin = low, indexOfMax = low, pivotIndex = low;
    for (int i = low + 1; i <= high; i++) {
        if (a[i].key < a[indexOfMin].key) indexOfMin = i;
        if (a[i].key > a[indexOfMax].key) indexOfMax = i;
    }
    float average = (a[indexOfMin].key + a[indexOfMax].key) / 2.0;
    for (int i = low + 1; i <= high; i++)
        if (abs(a[i].key - average) < abs(a[pivotIndex].key - average))
            pivotIndex = i;
    return pivotIndex;
}

// same version as the one we studied. average
int partitionOpt(record a[], int first, int last)
{
    int mid = (first + last) / 2;
    if (a[first].key < a[mid].key && a[mid].key < a[last].key) swap(a[mid], a[first]);
    else if (a[first].key > a[mid].key && a[mid].key > a[last].key) swap(a[mid], a[first]);
    else if (a[first].key < a[last].key && a[last].key < a[mid].key) swap(a[last], a[first]);
    else if (a[first].key > a[last].key && a[last].key > a[mid].key) swap(a[last], a[first]);
    record x = a[first]; int low = first, high = last;
    bool highTurn = true;

    while (low < high)
    {
        if (highTurn) {
            if (a[high].key < x.key) {
                a[low++] = a[high];
                highTurn = !highTurn;
            }
            else	high--;
        }
        else {
            if (a[low].key > x.key) {
                a[high--] = a[low];
                highTurn = !highTurn;
            }
            else	low++;
        }
    }
    a[low] = x;
    return low;
}

// same version as the one we studied.
int partition(record a[], int first, int last)
{
    record x = a[first];
    int low = first, high = last;
    bool highTurn = true;

    while (low < high)
    {
        if (highTurn) {
            if (a[high].key < x.key) {
                a[low++] = a[high];
                highTurn = false;
            }
            else	high--;
        }
        else {
            if (a[low].key > x.key) {
                a[high--] = a[low];
                highTurn = true;
            }
            else	low++;
        }
    }
    a[low] = x;
    return low;
}

void quickSort1(record nums[], int start, int end) {
    if (start >= end) return;

    int mid = partition(nums, start, end);

    quickSort1(nums, start, mid - 1);
    quickSort1(nums, mid + 1, end);
}

// quicksort
void sort7(record  nums[], int len) {
    quickSort1(nums, 0, len - 1);
}

void quickSort1Opt(record nums[], int start, int end) {
    if (start >= end) return;
    int k = end - start + 1;
    if (k < 18) {
        sort5(nums + start, k);
        return;
    }
    int mid = partitionOpt(nums, start, end);

    quickSort1Opt(nums, start, mid - 1);
    quickSort1Opt(nums, mid + 1, end);
}
void sort8(record  nums[], int len) {
    quickSort1Opt(nums, 0, len - 1);
}


void fixheap(record a[], int left, int right) {
    record x;

    x = a[left];

    int i, j;
    for (i = left, j = 2 * i + 1; j <= right; i = j, j = 2 * i + 1) {
        if (j < right) {
            if (a[j + 1].key > a[j].key) j++;
        }
        if (x.key >= a[j].key) {
            break;
        }
        a[i] = a[j];

    }
    a[i] = x;
}
void heapSort(record  a[], int n) {
    if (n > 1) {
        for (int left = n / 2 - 1; left >= 0; left--) {
            fixheap(a, left, n - 1);

        }

        swap(a[0], a[n - 1]);

        for (int right = n - 2; right >= 1; right--) {
            fixheap(a, 0, right);


            swap(a[0], a[right]);
        }
    }
}
// heapsort
void sort9(record a[], int len) {
    heapSort(a, len);
}

// radix sort
void sort10(record* nums, int len) {
    const int BASE = 10;
    vector<record> bucket[BASE];

    long long int maxi = nums[0].key;
    for (int j = 1; j < len; j++)
        if (nums[j].key > maxi)		maxi = nums[j].key; // find maximum
    int i;
    // iterate through each radix until n>maxi
    for (int n = 1; maxi >= n; n *= BASE) {
        // sort list of numbers into buckets
        for (i = 0; i < len; i++)
            bucket[(nums[i].key / n) % BASE].push_back(nums[i]);

        // merge buckets back to list
        for (int k = i = 0; i < BASE; bucket[i++].clear())
            for (vector<record>::iterator j = bucket[i].begin(); j != bucket[i].end(); nums[k++] = *(j++));
    }
}


void print(record nums[], int len, bool newLine) {
    if (newLine) cout << endl;
    for (int i = 0; i < len; i++)
        cout << nums[i].key << " ";
    cout << endl;
}

int random10(int powOf10) {
    if (powOf10 > 9) {
        cout << "Limit is 10^9" << endl;
        powOf10 = 9;
    }
    int num = 0;
    while (powOf10-- > 0)
        num = num * 10 + rand() % 10;
    return num;
}

// to fill the array with values, ascending, descending, random or shuffled
void fill(record nums[], int len, char orderCode) {
    int digits = int(log10(len + 0.5)); // will give # of digits in len 
    for (int i = 0; i < len; i++) {
        if (orderCode == 'a' || orderCode == 's') nums[i].key = i + 1;

        else if (orderCode == 'd') nums[i].key = len - i;
        else {
            nums[i].key = random10(digits + 1);  // random
        }
    }
    if (orderCode == 's') { // close to ascending with a minimal shuffle
        for (int i = 0; i <= len / 12; i++) {
            int loc1 = random10(digits + 1);
            int loc2 = random10(digits + 1);
            swap(nums[loc1 % len], nums[loc2 % len]);
        }
    }
}

void copyTo(record from[], record to[], int len) {
    for (int i = 0; i < len; i++)
        to[i] = from[i];
}

double timeIt(void (*sort)(record[], int), int size, int loops, bool printIt, int ocode)
{
    unsigned int tfine = 0, start = (unsigned int)time(0);

    for (int i = 0; i < loops; i++) {
        fill(buf1, size, ocode);   // we don't count this in the time
        copyTo(buf1, buf2, size); // nor this
        if (printIt) print(buf1, size, true);
        unsigned int clockStart = clock();
        sort(buf2, size);
        tfine += clock() - clockStart;
        if (printIt) print(buf2, size, false);
    }
    return   (int)(tfine * 1000.0 / CLOCKS_PER_SEC + 0.5001);  // elapsed time in milliseconds
}


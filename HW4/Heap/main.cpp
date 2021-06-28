#include "MaxPQ.h"
#include "MinPQ.h"

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
    MaxHeap<int> maxpq;
    MinHeap<int> minpq;

    cout << "Input the maxheap (heapSize key1 key2 ...):\n>> ";
    cin >> maxpq;
    cout << "The Maxheap array: " << maxpq << endl;

    cout << "The top of heap is " << maxpq.Top() << endl;
    maxpq.Pop();
    cout << "Pop out the top, and now the top is " << maxpq.Top() << endl;
    cout << "The hole heap become " << maxpq << endl;

    cout << "Input the minheap (heapSize key1 key2 ...):\n>> ";
    cin >> minpq;
    cout << "The Minheap array: " << minpq << endl;
    
    cout << "The top of heap is " << minpq.Top() << endl;
    minpq.Pop();
    cout << "Pop out the top, and now the top is " << minpq.Top() << endl;
    cout << "The hole heap become " << minpq << endl;

    cout << "Sort the maxheap, in descending order\n  [ ";
    while (!maxpq.IsEmpty()) {
        cout << maxpq.Top() << ' ';
        maxpq.Pop();
    }
    cout << "]\n";

    cout << "Sort the minheap, in ascending order\n  [ ";
    while (!minpq.IsEmpty()) {
        cout << minpq.Top() << ' ';
        minpq.Pop();
    }
    cout << "]\n";

    return 0;
}
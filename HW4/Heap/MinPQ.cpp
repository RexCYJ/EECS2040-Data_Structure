#include "MinPQ.h"

// template <class T>
// void ChangeSize1D(T* &start, int length, int newsize)
// {
//     if (length > newsize) throw "capacity insufficient";
//     T* newArray = new T[newsize + 1];
//     for (int i = 0; i <= length; i++)
//         newArray[i] = start[i];
//     delete [] start;
//     start = newArray;
// }

template <class T>
MinHeap<T>::MinHeap(int theCapacity)
{
    if (theCapacity < 1) throw "Capacity must be >= 1";
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity + 1];     // heap[0] is unused
}

template <class T>
bool MinHeap<T>::IsEmpty() const
{
    return (heapSize == 0);
}

template <class T>
const T& MinHeap<T>::Top() const
{
    return heap[1];
}

template <class T>
void MinHeap<T>::Push(const T& e)
{
    if (heapSize == capacity) {
        ChangeSize1D(heap, capacity, 2 * capacity);
        capacity *= 2;
    } 
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > e) {
        heap[currentNode] = heap[currentNode / 2] ;
        currentNode /= 2;
    }
    heap[currentNode] = e;
}

template <class T>
void MinHeap<T>::Pop()
{
    if (IsEmpty()) throw "Heap is Empty, cannot delete";
    heap[1].~T();
    T lastE = heap[heapSize--];
    int currentNode = 1;
    int child = 2;
    while (child <= heapSize) {
        // find the smallest child
        if (child < heapSize && heap[child] > heap[child + 1]) child++; 
        if (lastE <= heap[child]) break;    // satisfy the MinHeap 
        heap[currentNode] = heap[child];
        currentNode = child; child *= 2;
    }
    heap[currentNode] = lastE;
}

template <class T>
ostream& operator<<(ostream& os, const MinHeap<T>& pq)
{
    if (pq.heapSize == 0) return os;
    os << "[ ";
    for (int i = 1; i <= pq.heapSize; i++) {
        os << pq.heap[i] << ' ';
    }
    os << "]\n";
    return os;
}

template <class T>
istream& operator>>(istream& is, MinHeap<T>& pq)
{
    int n, i = 1;
    T input;
    is >> n;
    while (i <= n) {
        is >> input;
        pq.Push(input);
        i++;
    }
    return is;
}
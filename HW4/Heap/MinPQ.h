#ifndef MINPQ
#define MINPQ

#include <iostream>

using std::ostream;
using std::istream;

template <class T>
class MinPQ {
    public:
        virtual ~MinPQ() {}
        virtual bool IsEmpty() const = 0;
        virtual const T& Top() const = 0;
        virtual void Push(const T&) = 0;
        virtual void Pop() = 0;
};

template <class T>
class MinHeap;

template <class T>
ostream& operator<<(ostream&, const MinHeap<T>&);

template <class T>
istream& operator>>(istream&, MinHeap<T>&);

template <class T>
class MinHeap : public MinPQ<T>
{
    friend ostream& operator<< <>(ostream&, const MinHeap<T>&);
    friend istream& operator>> <>(istream&, MinHeap<T>&);
    public:
        MinHeap(int theCapacity = 10);
        bool IsEmpty() const;
        const T& Top() const;
        void Push(const T&);
        void Pop();
    private:
        T* heap;
        int heapSize;
        int capacity;
};

#include "MinPQ.cpp"

#endif 
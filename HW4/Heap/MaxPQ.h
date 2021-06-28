#ifndef MAXPQ
#define MAXPQ

#include <iostream>

using std::ostream;
using std::istream;

template <class T>
class MaxPQ {
    public:
        virtual ~MaxPQ() {}
        virtual bool IsEmpty() const = 0;
        virtual const T& Top() const = 0;
        virtual void Push(const T&) = 0;
        virtual void Pop() = 0;
};

template <class T>
class MaxHeap;

template <class T>
ostream& operator<<(ostream&, const MaxHeap<T>&);

template <class T>
istream& operator>>(istream&, MaxHeap<T>&);

template <class T>
class MaxHeap : public MaxPQ<T>
{
    friend ostream& operator<< <>(ostream&, const MaxHeap<T>&);
    friend istream& operator>> <>(istream&, MaxHeap<T>&);
    public:
        MaxHeap(int theCapacity = 10);
        bool IsEmpty() const;
        const T& Top() const;
        void Push(const T&);
        void Pop();
    private:
        T* heap;
        int heapSize;
        int capacity;
};

#include "MaxPQ.cpp"

#endif 
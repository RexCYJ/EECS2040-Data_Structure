#ifndef MYCIRQUEUE_H
#define MYCIRQUEUE_H

#include <iostream>
using std::endl;
using std::ostream;

template <class T>
class Queue;

template <class T>
ostream &operator<<(ostream& s, const Queue<T> &);

template <class T>
class Queue
{
    private:
        T* queue;
        int front, rear, capacity;
    public:
        Queue(int);
        bool IsEmpty() const;
        T& Front() const;
        T& Rear() const;
        int Get_capacity() const;
        int Get_size() const;
        Queue<T> merge(const Queue<T> &) const;
        void Push(const T& item);
        void Pop();
        friend ostream& operator<< <>(ostream&, const Queue<T> &);
};

#include "Queue.cpp"

#endif
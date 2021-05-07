#include <iostream>
#include "Queue.h"
using namespace std;

template <class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue = new T[capacity];
    front = rear = 0;
}

template <class T>
inline bool Queue<T>::IsEmpty() const {return front == rear;}

template <class T>
inline T& Queue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element";
    return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element";
    return queue[rear];
}

template <class T>
void Queue<T>::Push(const T& x)
{
    if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQueue);
        else {
            copy(queue + start, queue + capacity, newQueue);
            copy(queue, queue + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete [] queue;
        queue = newQueue;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}

template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    front = (front + 1) % capacity;
    queue[front].~T();
}

template <class T>
inline int Queue<T>::Get_capacity() const {return capacity;}

template <class T>
inline int Queue<T>::Get_size() const {return (rear - front + capacity) % capacity;}

template <class T>
Queue<T> Queue<T>::merge(const Queue<T> &b) const
{
    Queue<T> newQueue(capacity + b.capacity);
    int Acursor = (front + 1) % capacity,
        Bcursor = (b.front + 1) % b.capacity,
        Aend = (rear + 1) % capacity,
        Bend = (b.rear + 1) % b.capacity;
    int index = 0;

    while (Acursor != Aend && Bcursor != Bend) {
        newQueue.queue[index++] = queue[Acursor++];
        newQueue.queue[index++] = b.queue[Bcursor++];
        Acursor %= capacity;
        Bcursor %= b.capacity;
    }
    
    while (Acursor != Aend) {
        newQueue.queue[index++] = queue[Acursor++];
        Acursor %= capacity;
    }
    
    while (Bcursor != Bend) {
        newQueue.queue[index++] = queue[Bcursor++];
        Bcursor %= b.capacity;
    }

    newQueue.front = newQueue.capacity - 1;
    newQueue.rear = index - 1;

    return newQueue;
}

template<class T>
ostream &operator<<(ostream& s, const Queue<T> &A)
{
    int i = (A.front + 1) % A.capacity;

    s << "\tCapacity = " << A.capacity;
    s << "\tSize = " << A.Get_size() ;
    s << "\tqueue = (front: ";
    while (i != A.rear) {
        s << A.queue[i] << ", ";
        i = (i + 1) % A.capacity;
    }
    s << "rear: " << A.queue[A.rear] << ")\n";
    return s;
}
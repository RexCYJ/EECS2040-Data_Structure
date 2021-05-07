#ifndef BAD_AND_STACK_H
#define BAD_AND_STACK_H

#include <iostream>
using std::ostream;


template <class T>
class Bag
{
    protected:
        T* array;
        int capacity;
        int top;
    public:
        Bag(int bagCapacity = 10);
        virtual ~Bag();

        virtual int Size() const;
        virtual bool IsEmpty() const;
        virtual T& Element() const;
        int Get_capacity() const;
        void ChangeSize1D(T* &, const int, const int);

        virtual void Push(const T&);
        virtual void Pop();
};

template <class T>
class Stack;

template <class T>
class Queue;

template <class T>
ostream &operator<<(ostream&, const Stack<T> &);

template <class T>
ostream &operator<<(ostream&, const Queue<T> &);

template <class T>
class Stack: public Bag<T>
{
    using Bag<T>::array;
    using Bag<T>::capacity;
    using Bag<T>::top;
    using Bag<T>::IsEmpty;
    public:
        Stack(int stackCapacity = 10);
        ~Stack();
        T& Top() const;
        void Pop();
        friend ostream& operator<< <>(ostream&, const Stack<T> &);
};

template <class T>
class Queue: public Bag<T>
{
    protected:
        int front, rear;
        using Bag<T>::array;
        using Bag<T>::capacity;
        using Bag<T>::IsEmpty;
    public:
        Queue(int queueCapacity = 10);
        ~Queue();
        int Size() const;
        T& Front() const;
        T& Rear() const;
        virtual void Push(const T& item);
        void Pop();
        friend ostream& operator<< <>(ostream&, const Queue<T> &);
};

template <class T>
class Deque;

template <class T>
ostream &operator<<(ostream&, const Deque<T> &);

template <class T>
class Deque: public Queue<T>
{
    public:
        Deque(int dequeCapacity = 10);
        ~Deque();
        void Push(const T& item);
        void Eject();
        void Inject(const T& item);
        friend ostream& operator<< <>(ostream&, const Deque<T> &);
    protected:
        using Bag<T>::array;
        using Bag<T>::capacity;
        using Bag<T>::IsEmpty;
        using Queue<T>::front;
        using Queue<T>::rear;
};

#include "Bag.cpp"

#endif
#include "Bag.h"

using namespace std;

template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity)
{
    if (capacity < 1)
        throw "Capacity must be > 0";
    array = new T[capacity];
    top = -1;
}

template <class T>
Bag<T>::~Bag()
{delete [] array;}

template <class T>
inline int Bag<T>::Size() const
{return top + 1;}

template <class T>
bool Bag<T>::IsEmpty() const
{
    return (Size() == 0);
}

template <class T>
T& Bag<T>::Element() const
{
    if (IsEmpty())
        throw "Bag is empty";
    return array[0];
}

template <class T>
inline int Bag<T>::Get_capacity() const {return capacity;}

template <class T>        
void Bag<T>::ChangeSize1D(T* &a, const int oldsize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    T* temp = new T[newSize];
    int number = (newSize > oldsize)? oldsize: newSize;
    copy(a, a + number, temp);
    delete [] a;
    a = temp; 
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (capacity == top + 1) {
        ChangeSize1D(array, capacity, 2 * capacity);
        capacity *= 2;
    }
    array[++top] = x;
}

template <class T>
void Bag<T>::Pop()
{
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = top / 2;
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}

//////////////////////////////////////////////////////////////////////
// ---------------------- functions for stack ------------------------
//////////////////////////////////////////////////////////////////////

template <class T>
Stack<T>::Stack(int stackCapacity): Bag<T>(stackCapacity) {}

template <class T>
Stack<T>::~Stack() {}

template <class T>
T& Stack<T>::Top() const
{   
    if (IsEmpty()) throw "Stack is empty";
    return array[top];
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty. Cannot delete.";
    (top)--;
}

template <class T>
ostream& operator<<(ostream& s, const Stack<T> &A)
{
    s << " > S: " << A.Size() << ", C: " << A.Get_capacity() << ", Elements: (";
    if (A.IsEmpty()) {
        cout << " null )\n";
        return s;
    }
    for (int i = 0; i < A.top; i++)
        s << A.array[i] << ", ";
    s << A.array[A.top] << " <- top)\n";

    return s;
}

//////////////////////////////////////////////////////////////////////
// ----------------------- functions for queue -----------------------
//////////////////////////////////////////////////////////////////////

template <class T>
Queue<T>::Queue(int stackCapacity): Bag<T>(stackCapacity) 
{
    front = rear = 0;
}

template <class T>
Queue<T>::~Queue() {}

template <class T>
inline int Queue<T>::Size() const
{return (rear - front + capacity) % capacity;}

template <class T>
inline T& Queue<T>::Rear() const
{ 
    if (IsEmpty()) throw "Queue is empty. No rear element";
    return array[rear];
}

template <class T>
inline T& Queue<T>::Front() const
{ 
    if (IsEmpty()) throw "Queue is empty. No front element";
    return array[(front + 1) % capacity];
}

template <class T>
void Queue<T>::Push(const T& item) 
{
    if ((rear + 1) % (capacity) == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newQueue);
        else {
            copy(array + start, array + capacity, newQueue);
            copy(array, array + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete [] array;
        array = newQueue;
    }
    rear = (rear + 1) % capacity;
    array[rear] = item;
}

template <class T>
void Queue<T>::Pop() 
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    front = (front + 1) % (capacity);
    array[front].~T();
}

template <class T>
ostream& operator<<(ostream& s, const Queue<T> &A)
{
    int i = (A.front + 1) % A.capacity;
    s << " > S: " << A.Size() << ", C: " << A.Get_capacity() << ", Element: (front -> ";
    if (A.IsEmpty()) {
        cout << " null )\n";
        return s;
    }
    while (i != A.rear) {
        s << A.array[i] << ", ";
        i = (i + 1) % A.capacity;
    }
    s << A.array[A.rear] << " <- rear)\n";

    return s;
}

//////////////////////////////////////////////////////////////////////
// ----------------------- functions for deque -----------------------
//////////////////////////////////////////////////////////////////////

template <class T>
Deque<T>::Deque(int dequeCapacity): Queue<T>(dequeCapacity){}


template <class T>
Deque<T>::~Deque() {}

template <class T>
void Deque<T>::Push(const T& item)
{
    if ((front - 1 + capacity) % capacity == rear) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newQueue + 1);
        else {
            copy(array + start, array + capacity, newQueue + 1);
            copy(array, array + rear + 1, newQueue + capacity - start + 1);
        }
        front = 0;
        rear = capacity - 1;
        capacity *= 2;
        delete [] array;
        array = newQueue;
    }
    array[front] = item;
    front = (front - 1 + capacity) % capacity;
}

template <class T>
void Deque<T>::Eject()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete.";
    array[rear].~T();
    rear = (rear - 1 + capacity) % capacity;
}

template <class T>
void Deque<T>::Inject(const T& item)
{
    if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newQueue);
        else {
            copy(array + start, array + capacity, newQueue);
            copy(array, array + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete [] array;
        array = newQueue;
    }
    rear = (rear + 1) % capacity;
    array[rear] = item;
}

template <class T>
ostream& operator<<(ostream& s, const Deque<T> &A)
{
    int i = (A.front + 1) % A.capacity;
    s << " > S: " << A.Size() << ", C: " << A.Get_capacity() << ", Element: (front -> ";
    if (A.IsEmpty()) {
        cout << " null )\n";
        return s;
    }
    while (i != A.rear) {
        s << A.array[i] << ", ";
        i = (i + 1) % A.capacity;
    }
    s << A.array[A.rear] << " <- rear)\n";

    return s;
}
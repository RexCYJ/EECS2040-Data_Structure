#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::ostream;

template<class T> class List;

template<class T>
ostream &operator<<(ostream&, const List<T>&);

template<class T>
class Node {
    friend class List<T>;
    friend ostream &operator<< <>(ostream&, const List<T>&);
    private:
        T data;
        Node<T>* link;
};

template<class T>
class List {
    public:
        List() {first = NULL;}
        ~List();
        void InsertFront(const T&);
        void DeleteFront();
        void DeleteBack();
        T& Front() const;
        T& Back() const;
        T& Get(int) const;
        void Delete(int);
        void Insert(int, T);

        class Iterator;
        Iterator Begin();
        Iterator End();

        friend ostream &operator<< <>(ostream&, const List<T>&);
    private:
        Node<T>* first;
};

#include "Iterator.h"
#include "List.cpp"

#endif // LIST_H
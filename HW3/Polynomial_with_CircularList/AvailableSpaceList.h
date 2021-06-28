#ifndef AVAILABLE_SPACE_LIST_H
#define AVAILABLE_SPACE_LIST_H

#include "Polynomial.h"
#include <iostream>

template<class T>
class Chain;

template<class T>
class Node {
    friend class Chain<T>;
    friend class Polynomial;
    friend ostream& operator<<(ostream& s, Polynomial& a);
    friend istream& operator>>(istream& s, Polynomial& a);
    private:
        T data;
        Node<T> *link;
};

template<class T>
class Chain {
    friend class Polynomial;
    public:
        Chain();
        ~Chain();
        Node<T>* GetNode();
        void RetNode(Node<T>* &);
        void InsertFront(T &);
        void InsertBack(T &);
        void DeleteFront();
        // Node<T>* Read(Node<T> );
        const Chain<T>& operator=(const Chain<T>&);
        friend ostream& operator<<(ostream& s, Polynomial& a);
        friend istream& operator>>(istream& s, Polynomial& a);
    private:
        Node<T>* head;
        Node<T>* last;
        static Node<T>* av;
};

#include "AvailableSpaceList.cpp"

#endif // AVAILABLE_SPACE_LIST_H
#include "AvailableSpaceList.h"

template<class T>
Node<T>* Chain<T>::av = NULL;       // initailize av

template<class T>
Chain<T>::Chain()
{
    head = last = GetNode();    // get header node
    head->link = head;          // form a circular
}

template<class T>
Chain<T>::~Chain()
{
    Node<T> *temp;
    
    if (last) {
        temp = last->link;
        last->link = av;
        av = temp;
        last = NULL;
    }
}

template<class T>
Node<T>* Chain<T>::GetNode()
{
    Node<T> *x;
    if (av) {
        x = av;
        av = av->link;
    } else 
        x = new Node<T>;

    return x;
}

template<class T>
void Chain<T>::RetNode(Node<T>* &x)
{
    x->link = av;
    av = x;
    x = 0;
}

template<class T>
void Chain<T>::InsertFront(T &x)
{
    Node<T> *newnode = GetNode();
    newnode->link = head->link;
    head->link = newnode;
}

template<class T>
void Chain<T>::DeleteFront()
{
    Node<T> *temp = head->link;
    head->link = temp->link;
    RetNode(temp);
}

template<class T>
void Chain<T>::InsertBack(T &val)
{
    Node<T> *x = GetNode();
    last->link = x;
    x->link = head;
    x->data = val;
    last = x;
}

template<class T>
const Chain<T>& Chain<T>::operator=(const Chain<T> &a)
{
    Node<T> *atemp;
    if (head->link != head) {      // release from head to tail
        last->link = av;
        av = head->link;
    }
    head->link = head;
    last = head;
    atemp = a.head->link;
    while (atemp != a.head) {   // copy from head to tail
        InsertBack(atemp->data);
        atemp = atemp->link;
    }
    return a;
}
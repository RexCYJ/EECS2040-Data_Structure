#include "List.h"

using std::ostream;

template<class T>
typename List<T>::Iterator List<T>::Begin() 
{
    return Iterator(first);
}

template<class T>
typename List<T>::Iterator List<T>::End() 
{
    return Iterator(NULL);
}

template<class T>
List<T>::~List()
{
    List<T>::Iterator Cur(first);
    for (; Cur != NULL; Cur++)
        delete Cur.current;
}

template<class T>
void List<T>::InsertFront(const T& val)
{
    Node<T> *newNode = new Node<T>;
    newNode->link = first;
    newNode->data = val;
    first = newNode;
}

template<class T>
void List<T>::DeleteFront()
{
    if (first != NULL) {
        Node<T> *temp = first->link;
        delete first;
        first = temp;
    }
}

template<class T>
void List<T>::DeleteBack()
{
    List<T>::Iterator cur(first);
    for (; cur->link->link != NULL; cur++) {}
    delete cur->link;
    cur->link = NULL;
}

template<class T>
T& List<T>::Front() const
{
    return first->data;
}

template<class T>
T& List<T>::Back() const
{
    List<T>::Iterator cur(first);
    for (; cur->link != NULL; cur++) {}
    return cur->data;
}

template<class T>
T& List<T>::Get(int index) const
{
    List<T>::Iterator cur(first);
    for (int i = 1; cur != NULL && i < index; i++, cur++) {}
    if (cur != NULL) return cur->data;
    else throw "ERROR: Invalid access";
}

template<class T>
void List<T>::Delete(int index)
{
    List<T>::Iterator cur(first);
    if (index <= 1) {
        DeleteFront();
        return;
    }
    for (int i = 1; cur != NULL && i < index - 1; i++, cur++) {}
    if (cur != NULL) {
        if (cur->link == NULL) return;
        else {
            Node<T> *temp = cur->link->link;
            delete cur->link;
            cur->link = temp;
            return;
        }
    } else throw "ERROR: Invalid access";
}

template<class T>
void List<T>::Insert(int index, T val)
{
    List<T>::Iterator cur(first);
    if (index == 1) {
        InsertFront(val);
        return;
    }
    for (int i = 1; cur != NULL && i < index - 1; i++, cur++) {}
    if (cur != NULL) {
        Node<T> *newnode = new Node<T>;
        newnode->link = cur->link;
        cur->link = newnode;
        newnode->data = val;
    } else throw "ERROR: Invalid access";
}

template<class T>
ostream &operator<<(ostream& s, const List<T>& list)
{
    Node<T> *cur = list.first;
    s << "The list :\n( first -> ";
    while (cur != NULL) {
        s << cur->data << " -> ";
        cur = cur->link;
    }
    s << "NULL )\n";
    return s;
}
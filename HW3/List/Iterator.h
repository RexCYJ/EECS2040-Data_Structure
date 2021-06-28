#ifndef ITERATOR_H
#define ITERATOR_H

#include "List.h"

template<class T>
class List<T>::Iterator {
    friend class List<T>;
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* startNode = 0)
            {current = startNode;}
        T& operator*() const {return current->data;}
        Node<T>* operator->() const {return current;} // point to the next node
        Iterator& operator++()          // Preincrement
            {current = current->link; return *this;}
        Iterator operator++(int)       // Postincrement
            {Iterator old(this->current);
             current = current -> link;
             return old;}
        bool operator!=(const Iterator r)
            {return current != r.current;}
        bool operator==(const Iterator r)
            {return current == r.current;}
};

#endif //ITERATOR_H
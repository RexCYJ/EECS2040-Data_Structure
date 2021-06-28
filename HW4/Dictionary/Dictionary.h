#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>

using std::ostream;

template <class K, class E>
struct pair {K key; E element;};

template <class K, class E>
class Dictionary 
{
    public:
        virtual bool IsEmpty() const = 0;
        virtual pair<K,E>* Get(const K&) const = 0;
        virtual void Insert(const pair<K,E>&) = 0;
        virtual void Delete(const K&) = 0;
};

template <class K, class E>
class BST;

template <class K, class E>
ostream& operator<<(ostream&, const BST<K,E>&);

template <class T>
class Node
{
    template <class K, class E>
    friend class BST;
    
    template <class K, class E>
    friend ostream& operator<<(ostream&, const BST<K,E> &);
    
    public:
        Node(T Nodedata, Node<T> *leftNode = 0, Node<T> *rightNode = 0):
            data(Nodedata), leftChild(leftNode), rightChild(rightNode){}
    private:
        T data;
        Node<T> *rightChild;
        Node<T> *leftChild;
        Node<T> *next;
        static Node<T> *prev;
        int leftSize;
};

template <class K, class E>
class BST : public Dictionary<K,E>
{
    friend ostream& operator<< <>(ostream&, const BST<K,E>&);
    public:
        BST() {root = head = NULL;}
        void Inorder();
        bool IsEmpty() const;
        pair<K,E>* Get(const K&) const;
        void Insert(const pair<K,E>&);
        void Delete(const K&);
        pair<K,E> *RankGet(int);
        void Split(const K&, BST<K,E>& small, pair<K,E>* &mid, BST<K,E>& big);
    private:
        Node<pair<K,E>> *root;
        Node<pair<K,E>> *head;
};

#include "BST.cpp"

#endif
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

using std::ostream;

template <class T> class BinaryTree;
template <class T> class Node;

template <class T>
ostream& operator<<(ostream&, const BinaryTree<T>&);

template <class T>
class Node {
    friend class BinaryTree<T>;
    friend ostream& operator<< <>(ostream&, const BinaryTree<T>&);
    public:
        Node(T Nodedata, Node<T>* leftNode = 0, Node<T>* rightNode = 0):
            data(Nodedata), leftChild(leftNode), rightChild(rightNode){}
    private:
        T data;
        Node<T> *leftChild;
        Node<T> *rightChild;
        Node<T> *next;
        static Node<T> *prev;
        void inorder(Node<T>*, Node<T>* &);
        void preorder(Node<T>*, Node<T>* &);
        void postorder(Node<T>*, Node<T>* &);
};

template <class T>
class BinaryTree 
{
    public:
        BinaryTree();
        BinaryTree(Node<T> *);
        BinaryTree(BinaryTree<T>& bt1, T&, BinaryTree<T>& bt2);
        bool IsEmpty();
        BinaryTree<T> LeftSubtree();
        BinaryTree<T> RightSubtree();
        T RootData();

        Node<T>* Copy(Node<T> *);
        bool Equal(Node<T> *, Node<T> *);

        void Inorder();
        void Preorder();
        void Postorder();
        void Levelorder();
        void NonrecInorder();
        void NoStackInorder();
        bool operator==(const BinaryTree& t) const;       
        
        friend ostream& operator<< <>(ostream&, const BinaryTree<T>&);
    private:
        Node<T> *root;
        Node<T> *head;
};

#include "BinaryTree.cpp"

#endif

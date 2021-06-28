#include "BinaryTree.h"
#include <stack>
#include <queue>

template <class T>
Node<T>* Node<T>::prev = NULL;

template <class T>
void Node<T>::inorder(Node<T>* root, Node<T>* &head)
{
    if (root != NULL) {
        inorder(root->leftChild, head);
        if (head == NULL)  head = prev = root;
        else  prev = prev->next = root;
        inorder(root->rightChild, head);
    }
}

template <class T>
void Node<T>::preorder(Node<T>* cur, Node<T>* &head)
{
    if (cur != NULL) {
        if (head == NULL)  head = prev = cur;
        else  prev = prev->next = cur;
        preorder(cur->leftChild, head);
        preorder(cur->rightChild, head);
    }
}

template <class T>
void Node<T>::postorder(Node<T>* cur, Node<T>* &head)
{
    if (cur != NULL) {
        postorder(cur->leftChild, head);
        postorder(cur->rightChild, head);
        if (head == NULL)  head = prev = cur; 
        else  prev = prev->next = cur;
    }
}

template <class T>
BinaryTree<T>::BinaryTree()
{
    root = head = NULL;
}

template <class T>
BinaryTree<T>::BinaryTree(Node<T> *rt)
{
    root = rt;
    head = NULL;
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& bt1, T& rootdata, BinaryTree<T>& bt2)
{
    root = new Node<T>(rootdata, Copy(bt1.root), Copy(bt2.root));
    head = NULL;
}

template <class T>
Node<T>* BinaryTree<T>::Copy(Node<T> *origNode)
{
    if (!origNode) return 0;
    return new Node<T>(origNode->data,
                       Copy(origNode->leftChild),
                       Copy(origNode->rightChild));
}

template <class T>
bool BinaryTree<T>::Equal(Node<T> *a, Node<T> *b)
{
    if ((!a) && (!b)) return true;
    return (a && b
              && (a->data == b->data)
              && Equal(a->leftChild, b->leftChild)
              && Equal(a->rightChild, b->rightChild));
}

template <class T>
bool BinaryTree<T>::IsEmpty()
{
    return (root == NULL);
}

template <class T>
BinaryTree<T> BinaryTree<T>::LeftSubtree()
{
    BinaryTree<T> leftTree;
    leftTree.root = root->leftChild;
    return leftTree;
}

template <class T>
BinaryTree<T> BinaryTree<T>::RightSubtree()
{
    BinaryTree<T> rightTree;
    rightTree.root = root->rightChild;
    return rightTree;
}

template <class T>
T BinaryTree<T>::RootData()
{
    return root->data;
}

template <class T>
void BinaryTree<T>::Inorder()
{
    if (!IsEmpty()) {
        head = NULL;
        root->inorder(root, head);
        head->prev->next = NULL;          // the inorder list starts from head, connects by next
    }
}

template <class T>
void BinaryTree<T>::Preorder()
{
    if (!IsEmpty()) {
        head = NULL;
        root->preorder(root, head);
        head->prev->next = NULL;
    }
}

template <class T>
void BinaryTree<T>::Postorder()
{
    if (!IsEmpty()) {
        head = NULL;
        root->postorder(root, head);
        head->prev->next = NULL;
    }
}

template <class T>
void BinaryTree<T>::Levelorder()
{
    head = NULL;
    std::queue<Node<T>*> q;
    Node<T> *currentNode = root;
    while (currentNode) {
        if (head == NULL)  head = currentNode->prev = currentNode;          // Visit current node
        else  currentNode->prev = currentNode->prev->next = currentNode;
        if (currentNode->leftChild) q.push(currentNode->leftChild);
        if (currentNode->rightChild) q.push(currentNode->rightChild);
        if (q.empty()) {
            head->prev->next = NULL;
            return;
        }
        currentNode = q.front();
        q.pop();
    }
}

template <class T>
void BinaryTree<T>::NonrecInorder()
{
    head = NULL;
    std::stack<Node<T>*> s;
    Node<T> *currentNode = root;
    while(1) {
        while (currentNode) {
            s.push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.empty()) {
            head->prev->next = NULL;
            return;
        }
        currentNode = s.top();
        s.pop();
        if (head == NULL)  head = currentNode->prev = currentNode;
        else  currentNode->prev = currentNode->prev->next = currentNode;
        currentNode = currentNode->rightChild;
    }
}

template <class T>
void BinaryTree<T>::NoStackInorder()
{
    head = NULL;
    if (IsEmpty()) return;
    Node<T> *top = 0, *lastRight = 0, *p, *q, *r, *r1;
    p = q = root;
    while (1) {
        while (1) {
            if ((!p->leftChild) && (!p->rightChild)) {      // leaf
                if (head == NULL)  head = p->prev = p;      // Visit p
                else  p->prev = p->prev->next = p;
                break;
            }
            if (!p->leftChild) {        // visit p and move to p->rightchild
                if (head == NULL)  head = p->prev = p;      // visit p
                else  p->prev = p->prev->next = p;
                r = p->rightChild; p->rightChild = q;
                q = p; p = r;
            } else {
                r = p->leftChild; p->leftChild = q;
                q = p; p = r;
            }
        }   // inner while
        Node<T>* av = p;
        while (1) {
            if (p == root) {
                head->prev->next = NULL;
                return;      // the traversal is finished.
            }
            if (!q->leftChild) {        // q--->p, p is q's right child
                r = q->rightChild; q->rightChild = p;
                p = q; q = r;
            } else if (!q->rightChild) {            // p is q's left child
                r = q->leftChild; q->leftChild = p;
                p = q; q = r; 
                if (head == NULL)  head = p->prev = p;  // visit p
                else  p->prev = p->prev->next = p;
            } else {
                if (q == lastRight) {
                    r = top; lastRight = r->leftChild;
                    top = r->rightChild; 
                    r->leftChild = r->rightChild = NULL;
                    r = q->rightChild; q->rightChild = p;
                    p = q; q = r;
                } else {
                    if (head == NULL)  head = q->prev = q;  // visit q
                    else  q->prev = q->prev->next = q;
                    av->leftChild = lastRight; av->rightChild = top;
                    top = av; lastRight = q;
                    r = q->leftChild; q->leftChild = p;
                    r1 = q->rightChild; q->rightChild = r;
                    p = r1;
                    break;
                }
            }
        }   // inner while
    }   // outer while
}

template <class T>
bool BinaryTree<T>::operator==(const BinaryTree& t) const
{
    return Equal(root, t.root);
}

template <class T>
ostream& operator<<(ostream& os, const BinaryTree<T>& bt)
{
    Node<T> *cur;
    cur = bt.head;
    os << "[ ";
    while (cur != NULL) {
        os << cur->data << ' ';
        cur = cur->next;
    }
    os << "]\n";
    return os;
}
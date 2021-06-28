#include "Dictionary.h"

template <class T>
Node<T>* Node<T>::prev;

template <class K, class E>
bool BST<K,E>::IsEmpty() const
{
    return (root == NULL);
}

template <class K, class E>
pair<K,E>* BST<K,E>::Get(const K& k) const
{
    Node<pair<K,E>> *currentNode = root;
    while (currentNode) {
        if (k < currentNode->data.key)
            currentNode = currentNode->leftChild;
        else if (k > currentNode->data.key)
            currentNode = currentNode->rightChild;
        else
            return &(currentNode->data);
    }
    return 0;   // no match
}

template <class K, class E>
void BST<K,E>::Insert(const pair<K,E>& thePair)
{
    Node<pair<K,E>> *p = root, *pp = 0;
    while (p) {
        pp = p;
        if (thePair.key < p->data.key) p = p->leftChild;
        else if (thePair.key > p->data.key) p = p->rightChild;
        else {
            p->data.element = thePair.element; 
            return;
        }
    }
    p = new Node<pair<K,E>> (thePair);
    if (root) 
        if (thePair.key < pp->data.key) pp->leftChild = p;
        else pp->rightChild = p;
    else root = p;
}

template <class K, class E>
void BST<K,E>::Delete(const K& k)       // K: key
{
    if (root == NULL) return;
    Node<pair<K,E>> *p = root;  // current node
    Node<pair<K,E>> *prev = 0;
    while (p) {
        if (k > p->data.key) {
            prev = p;
            p = p->rightChild;
        } else if (k < p->data.key) {
            prev = p;
            p = p->leftChild;
        } else break;     // find it
    }

    Node<pair<K,E>> *rep, *prep = NULL;   // replaced node
    if (p == NULL) return;                // Couldn't find it
    if (!p->rightChild && !p->leftChild) {      // no child
        if (prev && (prev->leftChild == p)) prev->leftChild = 0;
        else if (prev && (prev->rightChild == p)) prev->rightChild = 0;
        delete p;
    } else if (p->rightChild && p->leftChild) {    // two child
        rep = p->leftChild;
        while (rep->rightChild) {           // search for the largest node in the left subtree
            prep = rep;
            rep = rep->rightChild;            
        }
        if (prep) {     // if replaced node is not directly connect to the removed node
            prep->rightChild = rep->leftChild;
            rep->leftChild = p->leftChild;
            rep->rightChild = p->rightChild;
            if (prev)   // it is not the root of this tree
                if (prev->leftChild == p) prev->leftChild = rep;
                else prev->rightChild = rep;
            else root = rep;
            delete p;
        } else {        // the replaced node is connected directly to the removed node
            if (prev)
                if (prev->leftChild == p) prev->leftChild = rep;
                else prev->rightChild = rep;
            else root = rep;
            rep->rightChild = p->rightChild;
            delete p;
        }
    } else if (p->leftChild && !p->rightChild) {    // only left child
        if (prev->leftChild == p) {                // p is prev's left child
            prev->leftChild = p->leftChild;
            delete p;
        } else {                                    // p is prev's right child
            prev->rightChild = p->leftChild;
            delete p;
        }
    } else if (!p->leftChild && p->rightChild) {    // only right child
        if (prev->leftChild == p) {        // p is prev's left child
            prev->leftChild = p->rightChild;
            delete p;
        } else {                            // p is prev's right child
            prev->rightChild = p->rightChild;
            delete p;
        }
    }
}

template <class K, class E>
void BST<K,E>::Inorder()
{
    head = NULL;
    if (IsEmpty()) return;
    Node<pair<K,E>> *top = 0, *lastRight = 0, *p, *q, *r, *r1;
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
        Node<pair<K,E>>* av = p;
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

template <class K, class E>
pair<K,E>* BST<K,E>::RankGet(int r)
{
    int i = 1;
    Node<pair<K,E>> *cur = head;
    Inorder();
    while (i < r) {
        cur = cur->next;
        i++;
    }
    return &cur->data;
}

// Split the BST with respect to key k
template <class K, class E>
void BST<K,E>::Split(const K& k, BST<K,E>& small, pair<K,E>* &mid, BST<K,E>& big)
{
    if (!root) {small.root = big.root = 0; return;}     // empty tree
    Node<pair<K,E>> *sHead = new Node<pair<K,E>> (*mid),
                    *s = sHead,
                    *bHead = new Node<pair<K,E>> (*mid),
                    *b = bHead,
                    *currentNode = root;
    while (currentNode) 
        if (k < currentNode->data.key) {
            b->leftChild = currentNode;
            b = currentNode; 
            currentNode = currentNode->leftChild;
        } else if (k > currentNode->data.key) {
            s->rightChild = currentNode;
            s = currentNode; 
            currentNode = currentNode->rightChild;
        } else {
            s->rightChild = currentNode->leftChild;
            b->leftChild = currentNode->rightChild;
            small.root = sHead->rightChild; delete sHead;
            big.root = bHead->leftChild; delete bHead;
            mid = new pair<K,E>;
            mid->key = currentNode->data.key;
            mid->element = currentNode->data.element;
            delete currentNode;
            return;
        }
    // no pair with key k
    s->rightChild = b->leftChild = 0;
    small.root = sHead->rightChild; delete sHead;
    big.root = bHead->leftChild; delete bHead;
    mid = 0;
    return;
}

template <class K, class E>
ostream& operator<<(ostream& os, const BST<K,E>& tree)
{
    Node<pair<K,E>> *cur;
    cur = tree.head;
    os << "[ ";
    while (cur != NULL) {
        os << cur->data.key << ": " << cur->data.element << ", ";
        cur = cur->next;
    }
    os << "]\n";
    return os;
}

#include "Dictionary.h"

using std::cout;
using std::endl;

int main(void)
{
    BST<int, char> dict;
    pair<int, char> *A;
    dict.Insert(pair<int,char>{50, 'A'});
    dict.Insert(pair<int,char>{5, 'B'});
    dict.Insert(pair<int,char>{30, 'C'});
    dict.Insert(pair<int,char>{40, 'D'});
    dict.Insert(pair<int,char>{80, 'E'});
    dict.Insert(pair<int,char>{35, 'F'});
    dict.Insert(pair<int,char>{2, 'G'});
    dict.Insert(pair<int,char>{20, 'H'});
    dict.Insert(pair<int,char>{15, 'I'});
    dict.Insert(pair<int,char>{60, 'J'});
    dict.Insert(pair<int,char>{70, 'K'});
    dict.Inorder();
    cout << "1. Insert the sequence:\n>> " << dict << endl; 
    
    dict.Delete(50);
    dict.Inorder();
    cout << "2. Delete the node with key 50:\n>> " << dict << endl; 
    
    A = dict.Get(40);
    cout << "3. Get the node with key 40:\n>> " << A->key << ", " << A->element << endl << endl;
    
    A = dict.RankGet(5);
    cout << "4. Get the rank-5 node\n>> " << A->key << ", " << A->element << endl << endl;
    
    BST<int, char> rightTree, leftTree;
    dict.Split(35, leftTree, A, rightTree);
    leftTree.Inorder();
    rightTree.Inorder();
    cout << "5. Split the tree with respect to key 35:\n";
    cout << ">> left tree:  " << leftTree;
    cout << ">> right tree: " << rightTree;
    cout << ">> Splited node: " << A->key << ", " << A->element << endl; 

    return 0;
}
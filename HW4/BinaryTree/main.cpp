#include "BinaryTree.h"

using std::cout;
using std::endl;

int main(void)
{
    Node<char> C8('A');
    Node<char> C9('B');
    Node<char> C7('C');
    Node<char> C5('D');
    Node<char> C3('E');
    Node<char> C6('-', &C8, &C9);
    Node<char> C4('*', &C6, &C7);
    Node<char> C2('*', &C4, &C5);
    Node<char> C1('+', &C2, &C3);
    BinaryTree<char> Tree1(&C1);

    Node<char> NH('H');
    Node<char> NJ('J');
    Node<char> NE('E');
    Node<char> NF('F');
    Node<char> NG('G');
    Node<char> ND('D', &NH, &NJ);
    Node<char> NB('B', &ND, &NE);
    Node<char> NC('C', &NF, &NG);
    Node<char> NA('A', &NB, &NC);
    BinaryTree<char> Tree2(&NA);

    char rootNode = 'X';

    Tree1.Inorder();
    Tree2.Inorder();
    cout << "1. Recursive Inorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;
    Tree1.Preorder();
    Tree2.Preorder();
    cout << "2. Recursive Preorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;
    Tree1.Postorder();
    Tree2.Postorder();
    cout << "3. Recursive Postorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;

    BinaryTree<char> Combine(Tree1, rootNode, Tree2);
    Combine.Inorder();
    cout << "4. Combine Tree1 and Tree2, displayed in inoder\n";
    cout << "   combination: " << Combine << endl;

    BinaryTree<char> Tree2_ST = Tree2.LeftSubtree();
    Tree2_ST.Inorder();
    cout << "5. Left subtree of Tree 2, displayed in inorder\n";
    cout << "   left subtree: " << Tree2_ST << endl;
    
    Tree2_ST = Tree2.RightSubtree();
    Tree2_ST.Inorder();
    cout << "6. Right subtree of Tree 2, displayed in inorder\n";
    cout << "   Right subtree: " << Tree2_ST << endl;

    Tree1.Postorder();  // rearrange the inorder sequence
    Tree2.Postorder();
    
    Tree1.NonrecInorder();
    Tree2.NonrecInorder();
    cout << "7. Non-recursive Inorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;

    Tree1.Postorder();  // reorganize the list
    Tree2.Postorder();

    Tree1.NoStackInorder();
    Tree2.NoStackInorder();
    cout << "8. Non-recursive, No stack Inorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;
    
    Tree1.Levelorder();
    Tree2.Levelorder();
    cout << "9. Levelorder\n";
    cout << "   Tree 1: " << Tree1 << "   Tree 2: " << Tree2 << endl;


    return 0;
}
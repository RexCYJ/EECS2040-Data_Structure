#include "SparseMatrix.h"

MatrixNode* Matrix::av = NULL;

MatrixNode* Matrix::Getnode(bool b, Triple* t)
{
    MatrixNode *x;
    if (av) {
        x = av;
        av = av->right;
        x->head = b;
        if (b) {x->next = x->right = x->down = x;} 
        else if (t == 0)
            throw "Null triple address is not acceptable";
        else
            x->triple = *t;
    } else
        x = new MatrixNode(b, t);
    return x;
}

void Matrix::Retnode(MatrixNode* &x)
{
    x->right = av;
    av = x;
    x = 0;
}


istream& operator>>(istream& is, Matrix& matrix)
{
    Triple s;
    is >> s.row >> s.col >> s.value;
    int p = (s.row > s.col)? s.row: s.col;
    matrix.headnode = matrix.Getnode(false, &s);
    
    // Zero Matrix;
    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
        return is;
    }

    // Set up row/col head node
    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) 
        head[i] = matrix.Getnode(true, 0);

    // read and fill the matrix
    int currentRow = 0;
    MatrixNode *last = head[0];             // last node in current row
    for (int i = 0; i < s.value; i++) {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) {           // current row is finished, record the last node
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }

        last = last->right = matrix.Getnode(false, &t);

        head[t.col]->next = head[t.col]->next->down = last;
    }
    last->right = head[currentRow];     // enclose the last row
    
    for (int i = 0; i < s.col; i++)     // enclose all column
        head[i]->next->down = head[i];
    
    for (int i = 0; i < p; i++)         // link the row/col head node
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    matrix.headnode->right = head[0];

    delete [] head;
    return is;
}

ostream& operator<<(ostream& os, const Matrix& a)
{    
    MatrixNode *rowhead = a.headnode->right;
    os<< ">> Rows: " << a.headnode->triple.row << "; Cols: " << a.headnode->triple.col ;
    os << "; Entries: " << a.headnode->triple.value;
    os << "\n>> row\tcol\tvalue\n";
    while (rowhead != a.headnode) {
        rowhead = rowhead->right;
        while (!rowhead->head) {
            os << ">> ";
            os << rowhead->triple.row << '\t';
            os << rowhead->triple.col << '\t';
            os << rowhead->triple.value << '\n';
            rowhead = rowhead->right;
        }
        rowhead = rowhead->next;
    }

    return os;
}

Matrix::Matrix()
{
    headnode = 0;
}

Matrix::Matrix(const Matrix& a)
{
    if (a.headnode == NULL) {
        headnode = NULL;
        return;
    }

    Triple asize = a.headnode->triple;
    int p = (asize.col > asize.row)? asize.col: asize.row;
    int currentRow = 0;
    MatrixNode *arowhead = a.headnode->right,
               *acur,
               *cur = headnode = Getnode(false, &(a.headnode->triple)),
               **head = new MatrixNode* [p];

    for (int i = 0; i < p; i++) {       // acquire row/col head node
        head[i] = Getnode(true, 0);
    }

    while (arowhead != a.headnode) {    // scan matrix a
        acur = arowhead->right;
        cur = head[currentRow];
        while (acur != arowhead) {
            cur = cur->right = Getnode(false, &(acur->triple));
            head[acur->triple.col]->next = head[acur->triple.col]->next->down = cur;
            acur = acur->right;
        }
        cur->right = head[currentRow++];  // close row
        arowhead = arowhead->next;
    }

    for (int i = 0; i < asize.col; i++)     // enclose all column
        head[i]->next->down = head[i];
    
    for (int i = 0; i < p; i++)         // link the row/col head node
        head[i]->next = head[i + 1];
    head[p - 1]->next = headnode;
    headnode->right = head[0];

    delete [] head;
}

Matrix::~Matrix()
{
    headnode = 0;
}

Matrix Matrix::operator+(const Matrix& b) const
{
    if ((headnode->triple.col != b.headnode->triple.col) 
        || (headnode->triple.row != b.headnode->triple.row))
        throw "Matrix mismatch";

    int entry = 0, i = 0, j = 0;    
    int headlen = (headnode->triple.col > headnode->triple.row)? 
                    headnode->triple.col : headnode->triple.row;
    Matrix newMat;
    MatrixNode *aCur, *bCur, *cCur;    
    MatrixNode** chead = new MatrixNode* [headlen];
    MatrixNode** leftElement = new MatrixNode* [headnode->triple.row];
    newMat.headnode = newMat.Getnode(false, &(headnode->triple));
    newMat.headnode->right = chead[0] = newMat.Getnode(true, 0);
    leftElement[0] = chead[0];
    for (i = 1; i < headlen; i++) {
        chead[i] = newMat.Getnode(true, 0);
        chead[i - 1]->next = chead[i];
        if (i < headnode->triple.row)
            leftElement[i] = chead[i];
    }
    chead[headlen - 1]->next = newMat.headnode;
    // newMat.headnode->triple = headnode->triple;

    aCur = headnode->right;
    bCur = b.headnode->right;
    cCur = newMat.headnode->right;
    entry = 0; j = 0; 
    while (aCur != headnode) {                          // column majar
        aCur = aCur->down; bCur = bCur->down;
        // merge columns from a and b into one column 
        while ((aCur->head == false) && (bCur->head == false)) {
            if (aCur->triple.row < bCur->triple.row) {
                cCur = cCur->down = newMat.Getnode(false, &(aCur->triple));
                aCur = aCur->down;
                entry++;
            } else if (aCur->triple.row > bCur->triple.row) {
                cCur = cCur->down = newMat.Getnode(false, &(bCur->triple));
                bCur = bCur->down;
                entry++;
            } else
                if (aCur->triple.value + bCur->triple.value) {
                    cCur = cCur->down = newMat.Getnode(false, &(bCur->triple));
                    cCur->triple.value += aCur->triple.value;
                    aCur = aCur->down; 
                    bCur = bCur->down;
                    entry++;
                }
        }
        while (aCur->head == false) {
            cCur = cCur->down = newMat.Getnode(false, &(aCur->triple));
            aCur = aCur->down;
            entry++;
        }
        while (bCur->head == false) {
            cCur = cCur->down = newMat.Getnode(false, &(bCur->triple));
            bCur = bCur->down;
            entry++;
        }

        cCur->down = chead[j];
        cCur = chead[j]->down;
        while (cCur->head == false) {         // connect the row pointer
            leftElement[cCur->triple.row] = leftElement[cCur->triple.row]->right = cCur;
            cCur = cCur->down;
        }

        aCur = aCur->next; bCur = bCur->next; cCur = cCur->next; 
        j++;
    }

    for (i = 0; i < headnode->triple.row; i++)
        leftElement[i]->right = chead[i];
    for (i; i < headlen; i++)
        chead[i]->right = chead[i];
    for (j = headnode->triple.col; j < headlen; j++)
        chead[j]->down = chead[j];
    newMat.headnode->triple.value = entry;

    return newMat;
}

// A * B, each rowA does inner product with columnB
Matrix Matrix::operator*(const Matrix& B) const
{
    int M = headnode->triple.row,
        P = headnode->triple.col,
        N = B.headnode->triple.col;
    Triple t;

    if (P != B.headnode->triple.row)
        throw "Matrix mismatch";

    Matrix C;
    MatrixNode *aCur = headnode->right, 
               *bCur = B.headnode->right,
               *cCur, *ahead, *bhead;
    int headlen = (M > N)? M : N;
    t = {M, N, 0};
    C.headnode = C.Getnode(false, &t);
    MatrixNode** chead = new MatrixNode* [headlen];
    MatrixNode** upElement = new MatrixNode* [N];
    C.headnode->right = chead[0] = C.Getnode(true, 0);
    upElement[0] = chead[0];
    for (int i = 1; i < headlen; i++) {         // Get and connect the head nodes
        chead[i] = C.Getnode(true, 0);
        chead[i - 1]->next = chead[i];
        if (i < N)
            upElement[i] = chead[i];
    }
    chead[headlen - 1]->next = C.headnode;      // encircular the head nodes

    int i = 0, j = 0, entry = 0;
    int sum;
    cCur = C.headnode->right;
    while (i < M) {         // row 
        ahead = aCur;
        bCur = B.headnode->right;
        cCur = chead[i];
        j = 0;
        while (j < N) {     // column
            sum = 0;
            bhead = bCur;
            aCur = aCur->right;
            bCur = bCur->down;
            while ((aCur->head == false) && (bCur->head == false)) {           // merge
                if (aCur->triple.col < bCur->triple.row) {
                    aCur = aCur->right;
                } else if (aCur->triple.col > bCur->triple.row) {
                    bCur = bCur->down;
                } else if (aCur->triple.col == bCur->triple.row) {
                    sum += aCur->triple.value * bCur->triple.value;
                    aCur = aCur->right; 
                    bCur = bCur->down;
                }
            }
            if (sum != 0) {
                t = {i, j, sum};
                cCur = cCur->right = C.Getnode(false, &t);
                upElement[j] = upElement[j]->down = cCur;
                entry++;
            }
            bCur = bhead->next;
            aCur = ahead;
            j++;
        }       // end of column
        cCur->right = chead[i];         // close the row
        aCur = ahead->next;
        i++;
    }           // end of row
    C.headnode->triple.value = entry;
    for (j = 0; j < N; j++)             // close columns
        upElement[j]->down = chead[j];    
    for (j = N; j < headlen; j++)
        chead[j]->down = chead[j];
    for (i = M; i < headlen; i++)
        chead[i]->right = chead[i];
    
    return C;
}

void Matrix::Transpose()
{
    if (!headnode) return;

    int tempint;
    MatrixNode *colhead = headnode->right;
    MatrixNode *curnode, *temp;
    while (colhead != headnode) {
        curnode = colhead->down;
        // swap down and right in colhead
        colhead->down = colhead->right;
        colhead->right = curnode;
        while (curnode != colhead) {
            // swap down and right in curnode
            temp = curnode->right;
            curnode->right = curnode->down;
            curnode->down = temp;

            // swap row and col in curnode
            tempint = curnode->triple.row;
            curnode->triple.row = curnode->triple.col;
            curnode->triple.col = tempint;

            curnode = curnode->right;
        }
        colhead = colhead->next;
    }
    tempint = headnode->triple.col;
    headnode->triple.col = headnode->triple.row;
    headnode->triple.row = tempint;
}
#include "SparseMatrix.h"
#include <iostream>

using namespace std;
using std::cin;
using std::cout;

SparseMatrix::SparseMatrix(int r = 0, int c = 0, int t = 0)
{
    rows = r; cols = c; terms = t;
    capacity = terms + 1;
    smArray = new MatrixTerm[capacity];
}

int SparseMatrix::get_cols() const
{
    return cols;
}

int SparseMatrix::get_rows() const
{
    return rows;
}

int SparseMatrix::get_terms() const
{
    return terms;
}

int SparseMatrix::get_capacity() const
{
    return capacity;
}

MatrixTerm* SparseMatrix::get_smArray() const
{
    return smArray;
}

void SparseMatrix::get_term(int i, int &r, int &c, int &v) const
{
    r = smArray[i].row;
    c = smArray[i].col;
    v = smArray[i].value;
}

// transpose the matrix, O(terms*cols) ~ O(rows*cols^2)
SparseMatrix SparseMatrix::Transpose() const
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0) {
        int currentB = 0;
        for (int c = 0; c < cols; c++)
            for (int i = 0; i < terms; i++)
                if (smArray[i].col == c) {
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB++].value = smArray[i].value;
                }
    }
    return b;
}

SparseMatrix SparseMatrix::FastTranspose() const
{
    SparseMatrix b(cols, rows, terms);
    int i;
    if(terms > 0) {
        int *rowSize = new int[cols];       // the number of nonzero elements in each row
        int *rowStart = new int[cols];      // the starting position of row i in b
        for (i = 0; i < cols; i++)  rowSize[i] = 0;
        for (i = 0; i < terms; i++) rowSize[smArray[i].col]++;

        rowStart[0] = 0;
        for (i = 1; i < cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

        for (i = 0; i < terms; i++) {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}

SparseMatrix SparseMatrix::Add(const SparseMatrix b)
{
    if (cols != b.cols || rows != b.rows) 
        throw "The matrics size are not the same";
    
    SparseMatrix temp(rows, cols, 0);
    int i = 0, j = 0, p = 0;

    while (i < terms && j < b.terms) {
        if (smArray[i].row > b.smArray[j].row) {
            temp.append(b.smArray[j++]);
        } else if (smArray[i].row == b.smArray[j].row) {
            if (smArray[i].col > b.smArray[j].col) {
                temp.append(b.smArray[j++]);
            } else if (smArray[i].col == b.smArray[j].col) {
                MatrixTerm a;
                a.row = smArray[i].row;
                a.col = smArray[i].col;
                a.value = smArray[i++].value + b.smArray[j++].value;
                temp.append(a);
            } else if (smArray[i].col < b.smArray[j].col) {
                temp.append(smArray[i++]);
            }
        } else if (smArray[i].row < b.smArray[j].row) {
            temp.append(smArray[i++]);
        }
    }

    while (i < terms)
        temp.append(smArray[i++]);

    while (j < b.terms)
        temp.append(b.smArray[j++]);

    return temp;
}

// return *this x b
SparseMatrix SparseMatrix::Multiply(const SparseMatrix b)
{   
    if (cols != b.cols) throw "Incompatible Matrices";
    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);
    int currRowIndex = 0,
        currRowBegin = 0,
        currRowA = smArray[0].row;
    // set boundary condition
    if (terms == capacity) ChangeSize1D(terms + 1);
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;
    int sum = 0;
    while (currRowIndex < terms) {
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms) {
            if (smArray[currRowIndex].row != currRowA) {
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;
                currRowIndex = currRowBegin;
                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;
                currColB = bXpose.smArray[currColIndex].row;
            } else if (bXpose.smArray[currColIndex].row != currColB) {
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            } else {
                if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col) 
                    currRowIndex++;
                else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col) {
                    sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
                    currRowIndex++; currColIndex++;
                } else {
                    currColIndex++;
                }
            }
        } // a round of column
        while (smArray[currRowIndex].row == currRowA)
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    }
    return d;
}

void SparseMatrix::append(MatrixTerm item)
{
    if (terms == capacity) {
        this->ChangeSize1D(capacity * 2);
    }
    if (item.value != 0)
        smArray[terms++] = item;
}

void SparseMatrix::append(int r, int c, int v)
{
    if (terms == capacity) {
        ChangeSize1D(capacity * 2);
    }
    if (v != 0) {
        smArray[terms].col = c;
        smArray[terms].row = r;
        smArray[terms++].value = v;
    }
}

void SparseMatrix::ChangeSize1D(const int newSize)
{
    if (newSize < terms)
        throw "New size must be >= number of terms";
    
    MatrixTerm *temp = new MatrixTerm[newSize];
    copy(smArray, smArray + terms, temp);
    delete [] smArray;
    smArray = temp;
    capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if (sum != 0) {
        if (terms == capacity)
            ChangeSize1D(2 * capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

istream& operator>>(istream& s, SparseMatrix& A)
{
    int i = 1, row, col, value;
    char c;

    cout << i << ")  ";
    s >> row;
    while (row != -1) {
        s >> col >> value;
        if (row >= A.get_rows() || col >= A.get_cols() || row < 0 || col < 0)
            throw "row or column out of range";
        A.append(row, col, value);
        cout << ++i << ")  ";
        s >> row;
    }
    return s;
}

ostream& operator<<(ostream& s, const SparseMatrix& A)
{
    int r, c, v;
    int currIndex = 0, currCol = 0, currRow = 0;

    s << "\trow: " << A.get_rows() << "\tcolumn: " << A.get_cols() << endl;
    s << "\tNone zero entries: " << A.get_terms() << endl;
    for (currIndex = 0; currIndex < A.get_terms(); currIndex++) {
        A.get_term(currIndex, r, c, v);
        s << "\tindex " << currIndex << ": ( " << r << ", " << c << ", " << v << " )" << endl;
    }
    s << '\t';
    for (currIndex = 0; currIndex < A.get_terms(); currIndex++) {
        A.get_term(currIndex, r, c, v);
        for (; currRow < r; currRow++) {
            for (; currCol < A.get_cols(); currCol++)
                cout << "0" << '\t';
            currCol = 0;
            cout << endl << '\t';
        }
        for (; currCol < c; currCol++)
            cout << "0" << '\t';
        cout << v << '\t';
        currCol = c + 1;
        if (currCol == A.get_cols()) {
            currCol = 0;
            currRow++;
            cout << endl << '\t';
        }
    }
    for (; currRow < A.get_rows(); currRow++) {
        for (; currCol < A.get_cols(); currCol++)
            cout << "0" << '\t';
        cout << endl << '\t';
        currCol = 0;
    }

    s << endl;
    return s;
}
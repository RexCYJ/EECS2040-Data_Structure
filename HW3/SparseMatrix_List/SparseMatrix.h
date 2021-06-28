#ifndef SPARSEMATRIX_LIST_H
#define SPARSEMATRIX_LIST_H

#include <iostream>

using std::istream;
using std::ostream;

struct Triple {int row, col, value;};

class Matrix;

istream& operator>>(istream&, Matrix&);
ostream& operator<<(ostream&, const Matrix&);

class MatrixNode {
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, const Matrix&);
    private:
        MatrixNode *down, *right;
        bool head;
        union {
            MatrixNode *next;
            Triple triple;
        };
        MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple *t)
{
    head = b;
    if (b) {next = right = down = this;} 
    else triple = *t;
}

class Matrix {
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, const Matrix&);
    public:
        Matrix();
        Matrix(const Matrix&);
        ~Matrix();
        Matrix operator+(const Matrix&) const;
        Matrix operator*(const Matrix&) const;
        void Transpose();
    private:
        MatrixNode* Getnode(bool, Triple*);
        void Retnode(MatrixNode* &);
        static MatrixNode *av;
        MatrixNode *headnode;
};

#include "SparseMatrix.cpp"

#endif
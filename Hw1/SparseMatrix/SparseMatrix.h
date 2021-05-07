#ifndef SPARSEMATRIX
#define SPARSEMATRIX

#include <iostream>
using std::ostream;
using std::istream;

class SparseMatrix;

class MatrixTerm
{
    friend class SparseMatrix;
    private:
        int row, col, value;
};

class SparseMatrix
{
    private:
        int rows, cols, terms, capacity;
        MatrixTerm *smArray;
    public:
        int get_terms() const;
        int get_cols() const;
        int get_rows() const;
        int get_capacity() const;
        MatrixTerm* get_smArray() const;
        void get_term(int, int&, int&, int&) const;

        SparseMatrix(int, int, int);
        SparseMatrix Transpose() const;
        SparseMatrix FastTranspose() const;
        SparseMatrix Add(const SparseMatrix);
        SparseMatrix Multiply(const SparseMatrix);
        void append(MatrixTerm);
        void append(int, int, int);
        void ChangeSize1D(const int);
        void StoreSum(const int, const int, const int);
};

istream& operator>>(istream&, SparseMatrix&);
ostream& operator<<(ostream&, const SparseMatrix&);

#endif
#include "SparseMatrix.h"

using std::cout;
using std::cin;

int main(void)
{
    Matrix A;

    cout << "Input Matrix A: \n";
    cin >> A;
    cout << "Matrix A:\n" << A;
    A.Transpose();
    cout << "Transpose A:\n" << A;
    A.Transpose();
    cout << "Transpose A again:\n" << A;
    Matrix B(A);
    cout << "Matrix B copy from A:\n" << B;
    cout << "Input matrix B :\n";
    cin >> B;
    Matrix C;
    C = A + B;
    cout << "Matrix C = B + A:\n" << C;
    C = A * B;
    cout << "Matrix C = B * A:\n" << C;

    return 0;
}
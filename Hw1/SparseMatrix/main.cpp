#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

using namespace std;
using std::cin;
using std::cout;

int main(void)
{
    int row, col;

    ifstream in("in.txt");
    ofstream out("out.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    auto coutbuf = std::cout.rdbuf(out.rdbuf());

    // ------------First Run------------
    cout << "Input the first matrix:" << endl;
    cout << "rows: ";   cin >> row;
    cout << "cols: ";   cin >> col;
    SparseMatrix A(row, col, 0);
    cout << "terms: " << endl;  cin >> A;
    cout << "Input the second matrix:" << endl;
    cout << "rows: ";   cin >> row;
    cout << "cols: ";   cin >> col;
    SparseMatrix B(row, col, 0);
    cout << "terms: " << endl;  cin >> B;

    cout << endl << "A:" << endl << A << "B:" << endl << B;
    cout << "Transpose of B:\n" << B.FastTranspose();
    cout << "A + B = " << endl << A.Add(B);
    cout << "A * B = " << endl << A.Multiply(B);

    // ------------Second Run------------
    cout << "Input the first matrix:" << endl;
    cout << "rows: ";   cin >> row;
    cout << "cols: ";   cin >> col;
    SparseMatrix C(row, col, 0);
    cout << "terms: " << endl;  cin >> C;
    cout << "Input the second matrix:" << endl;
    cout << "rows: ";   cin >> row;
    cout << "cols: ";   cin >> col;
    SparseMatrix D(row, col, 0);
    cout << "terms: " << endl;  cin >> D;

    cout << "C:" << endl << C << "D:" << endl << D;
    cout << "Transpose of D:\n" << D.FastTranspose();
    cout << "C + D = " << endl << C.Add(D);
    cout << "C * D = " << endl << C.Multiply(D);

    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

    return 0;
}
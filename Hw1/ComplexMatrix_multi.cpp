#include <iostream>

using namespace std;

void Mult(float**, float**, int n, float**);
void Add(float**, float**, int n, float**);
void Sub(float**, float**, int n, float**);

int main(void)
{
    int n;
    cin >> n;
    float A[n][n], B[n][n], C[n][n], D[n][n];
    float AC[n][n], AD[n][n], BC[n][n], BD[n][n];
    float Real[n][n], Image[n][n];

    Mult(A, C, n, AC);
    Mult(A, D, n, AD);
    Mult(B, C, n, BC);
    Mult(B, D, n, BD);
    Add(AD, BC, n, Image);      // (AD + BC)i
    Sub(AC, BD, n, Real);       // (AC - BD)

    return 0;
}

void Mult(float**A, float**B, int n, float**AB)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AB[i][j] = 0;
            for (int k = 0; k < n; k++)
                AB[i][j] += A[i][k] * B[k][j];
        }
    }
}

void Add(float**A, float**B, int n, float**C)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void Sub(float**A, float**B, int n, float**C)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}
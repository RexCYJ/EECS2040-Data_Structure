#include <iostream>
#include "Polynomial.h"

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
    Polynomial F, G;
    Polynomial Cal;
    double in;

    cout << "Type the first polynomial F(x): ";
    cin >> F;
    cout << "F(x) = " << F << endl;
    Polynomial K(F);
    cout << "Copy F(x) : " << K;
    cout << "\nType the second polynomial G(x): ";
    cin >> G;
    cout << "G(x) = " << G << endl;
    Cal = F + G;
    cout << "F(x) + G(x) = " << Cal;
    Cal = F - G;
    cout << "F(x) - G(x) = " << Cal;
    Cal = F * G;
    cout << "F(x) * G(x) = " << Cal;
    cout << "x = ? ";
    cin >> in;
    cout << "Eval(x) = " << Cal.Evaluate(in) << endl;
    return 0;
}
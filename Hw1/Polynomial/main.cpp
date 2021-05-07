#include <iostream>
#include <fstream>
#include "Polynomial.h"

using namespace std;
using std::cin;
using std::cout;

int main(void)
{
    Polynomial f, g, output;
    float x;
    long start, stop;
    ifstream in("input.txt");
    ofstream out("output.txt");
    auto cin_buf = cin.rdbuf(in.rdbuf());
    auto cout_buf = cout.rdbuf(out.rdbuf());

    // First run
    cout << "-----------First Run------------" << endl;
    cout << "Input two polynomials" << endl;
    cout << "e.g: x^100+6x^12-10.22x^1+1/" << endl;
    cout << "f(x) = ";
    cin >> f;
    cout << "g(x) = ";
    cin >> g;
    cout << "\nYour input f(x) = " << f << endl;
    cout << "Your input g(x) = " << g << endl;
    cout << "g(x) + f(x) = " << g + f << endl;
    cout << "g(x) * f(x) = " << g.Mult(f) << endl;
    cout << "input x = ";
    cin >> x;
    cout << "f( " << x << " ) = " << f.Eval(x) << endl <<endl;
    g.reset();
    f.reset();
    
    // Second run
    cout << "-----------Second Run------------" << endl;
    cout << "Input two polynomials" << endl;
    cout << "e.g: x^100+6x^12-10.22x^1+1/" << endl;
    cout << "f(x) = ";
    cin >> f;
    cout << "g(x) = ";
    cin >> g;
    cout << "\nYour input f(x) = " << f << endl;
    cout << "Your input g(x) = " << g << endl;
    cout << "g(x) + f(x) = " << g + f << endl;
    cout << "g(x) * f(x) = " << g.Mult(f) << endl;
    cout << "input x = ";
    cin >> x;
    cout << "f( " << x << " ) = " << f.Eval(x) << endl;

    cin.rdbuf(cin_buf);
    cout.rdbuf(cout_buf);

    return 0;
}
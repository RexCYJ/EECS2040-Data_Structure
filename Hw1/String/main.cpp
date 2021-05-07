#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;
using std::cin;
using std::cout;

int main(void)
{   
    int a, b;
    char c;
    char init[1] = {'\0'}, init2[1] = {'\0'};
    String S(init, 10);
    String Pat(init2, 10);
    ifstream in("in.txt");
    ofstream out("out.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
    auto coutbuf = cout.rdbuf(out.rdbuf());

    // -------------First Run-------------
    cout << "----<Run 1>--------------------------------------" << endl;
    cout << "Type your input string:" << endl;
    cin >> S;
    cout << "Type the searching pattern:" << endl;
    cin >> Pat;
    cout << "1) Your Input:\n   S:  \t"<< S << "\n   Pat:\t" << Pat << endl;
    cout << "2) The length of input is " << S.Length() << endl;
    cout << "3) Concat the input and pattern:\n      " << S.Concat(Pat);
    cout << "4) The first pattern in the input string is at " << S.Find(Pat) << endl;
    // cin.rdbuf(cinbuf);
    cout << "5) Select a section to be deleted. S.Delete(start, length)\n\t> Start:   "; cin >> a;
    cout << "\t> length:  "; cin >> b;
    cout << "\n   Current string:\n     " << S.Delete(a, b);
    cout << "6) Select a piece. S.Substr(start, length)\n\t> Start:   "; cin >> a;
    cout << "\t> length:  "; cin >>b;
    cout << "\n   Current string:\n     " << S.Substr(a, b);
    // cin >> c;

    // -------------Second Run-------------
    // cin.rdbuf(in.rdbuf());
    cout << endl << "----<Run 2>--------------------------------------" << endl;
    cout << "Type your input string:" << endl;
    cin >> S;
    cout << "Type the searching pattern:" << endl;
    cin >> Pat;
    cout << "1) Your Input:\n   S:  \t"<< S << "\n   Pat:\t" << Pat << endl;
    cout << "2) The length of input is " << S.Length() << endl;
    cout << "3) Concat the input and pattern:\n      " << S.Concat(Pat);
    cout << "4) The first pattern in the input string is at " << S.Find(Pat) << endl;
    // cin.rdbuf(cinbuf);
    cout << "5) Select a character to be deleted. S.CharDelete(char)\n\t> Char:   "; cin >> c;
    cout << "\n   Current string:\n     " << S.CharDelete(c);
    cout << "6) Select a piece. S.Substr(start, length)\n\t> Start:   "; cin >> a;
    cout << "\t> length:  "; cin >>b;
    cout << "\n   Current string:\n     " << S.Substr(a, b);
 
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    
    return 0;
}
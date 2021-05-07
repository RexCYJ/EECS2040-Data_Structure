#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;
using std::cin;
using std::cout;

class String
{
    private:
        char *str;
        int *f;
        int len;    // length of str storage
    public:
        String(char *, int);
        bool operator==(String) const;
        bool operator!() const;
        int Length() const;
        String Concat(const String);
        String Substr(int, int);
        int Find(String);
        void FailureFunction();
        String Delete(int, int);
        String CharDelete(char);
        friend istream& operator>>(istream&, String &);
        friend ostream& operator<<(ostream&, const String &);
};

istream& operator>>(istream&, String &);
ostream& operator<<(ostream&, const String &);

#endif
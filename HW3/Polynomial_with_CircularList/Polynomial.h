#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

using std::istream;
using std::ostream;

class Polynomial;

#include "AvailableSpaceList.h"

typedef struct term {
    double coef;
    int exp;
} Term;

istream& operator>>(istream&, Polynomial&);
ostream& operator<<(ostream&, Polynomial&);

class Polynomial {
    public:
        Polynomial();
        Polynomial(const Polynomial&);
        ~Polynomial();
        Polynomial& operator+(const Polynomial& b) const;
        Polynomial& operator-(const Polynomial& b) const;
        Polynomial& operator*(const Polynomial& b) const;
        void Multi_coef(const double c);
        void Multi_exp(const int e);
        const Polynomial& operator=(const Polynomial& b);
        double Evaluate(double x) const;
        friend istream& operator>>(istream&, Polynomial&);
        friend ostream& operator<<(ostream&, Polynomial&);
    private:
        Chain<Term> poly;
};

#include "Polynomial.cpp"

#endif // POLYNOMIAL_H
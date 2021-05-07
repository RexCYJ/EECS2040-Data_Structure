#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
using std::ostream;
using std::istream;

class Polynomial;

class Term
{
    friend Polynomial;
    private:
        float coef;
        int exp;
};

class Polynomial
{
    private:
        Term* termArray;    // array of nonzero terms
                            // aligned in decreasing exponential
        int terms;          // number of none zero terms
        int capacity;       // size of termArray
    public:
        Polynomial();

        // functions for reading polynomial
        int term() const;
        int cap() const;
        // Term* termarray() const;
        int tarray_exp(int) const;
        float tarray_coef(int) const;
        
        // functions for modifying polynomial 
        void set_tarray_exp(int, int);
        void set_tarray_coef(int, float);
        // void set_tarray_addr(Term*);

        void reset();   // clear polynomial

        void operator=(const Polynomial&);

        void copy(Term*, Term*, Term*);
        void NewTerm(float, int);
        float Eval(float);
        Polynomial Mult(Polynomial);
};

Polynomial operator*(const float&, const Polynomial&);
Polynomial operator^(const Polynomial&, const int&);
Polynomial operator+(const Polynomial&, const Polynomial&);
Polynomial operator*(const Polynomial&, const Polynomial&);

istream &operator>>(istream&, Polynomial&);
ostream &operator<<(ostream&, Polynomial const);

#endif
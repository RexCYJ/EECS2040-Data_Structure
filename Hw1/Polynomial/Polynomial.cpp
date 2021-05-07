#include <iostream>
#include "Polynomial.h"

using namespace std;
using std::cin;
using std::cout;

// constructor of polynomial
Polynomial::Polynomial(){
    terms = 0;
    capacity = 1;
    termArray = new Term[capacity];
    termArray[0].coef = 0;
    termArray[0].exp = 0;
}

int Polynomial::term() const    // get polynomial.terms
{
    return terms;
}

int Polynomial::cap() const     // get polynomial.capacity
{
    return capacity;
}

// Term* Polynomial::termarray() const
// {
//     return termArray; 
// }

int Polynomial::tarray_exp(int ind) const       // get exponential of termArray[ind]
{
    return termArray[ind].exp;
}

float Polynomial::tarray_coef(int ind) const    // get coefficient of termArray[ind]
{
    return termArray[ind].coef;
}

void Polynomial::set_tarray_exp(int ind, int newexp)    // modify the exponential
{
    termArray[ind].exp = newexp;
}

void Polynomial::set_tarray_coef(int ind, float newcoef)    // modify the coefficient
{
    termArray[ind].coef = newcoef;
}

// void Polynomial::set_tarray_addr(Term* newTermArray)
// {
//     delete [] termArray;
//     termArray = newTermArray;
// }

void Polynomial::reset()
{
    this->capacity = 1;
    this->terms = 0;
    delete [] this->termArray;
    termArray = new Term[capacity];
    termArray[0].coef = 0;
    termArray[0].exp = 0;
}

void Polynomial::operator=(const Polynomial& b)
{
    terms = b.terms;
    capacity = b.capacity;
    delete [] termArray;
    termArray = b.termArray;
}

// copy a polynomial from start to end, excluse end, to destination
void Polynomial::copy(Term* start, Term* end, Term* destination)
{
    for (int i = 0; &(start[i]) != end; i++) {
        destination[i].coef = start[i].coef;
        destination[i].exp = start[i].exp;
    }
}

// Add new term to the polynomial
void Polynomial::NewTerm(float newCoef, int newExp)
{
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[terms].coef = newCoef;
    termArray[terms++].exp = newExp;
}

// add up two polynomials
Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < a.term()) && (bPos < b.term())) {
        if (a.tarray_exp(aPos) == b.tarray_exp(bPos)) {
            float t = a.tarray_coef(aPos) + b.tarray_coef(bPos);
            if (t != 0)  c.NewTerm(t, a.tarray_exp(aPos));
            aPos++; bPos++;
        } else if (a.tarray_exp(aPos) > b.tarray_exp(bPos)) {
            c.NewTerm(a.tarray_coef(aPos), a.tarray_exp(aPos));
            aPos++;
        } else {
            c.NewTerm(b.tarray_coef(bPos), b.tarray_exp(bPos));
            bPos++;
        }

    }
    for (; aPos < a.term(); aPos++)
        c.NewTerm(a.tarray_coef(aPos), a.tarray_exp(aPos));
    for (; bPos < b.term(); bPos++)
        c.NewTerm(b.tarray_coef(bPos), b.tarray_exp(bPos));
    return c;
}

// scale the polynomial with a floating number
Polynomial operator*(const float& scaler, const Polynomial& a)
{
    Polynomial c;
    if (scaler != 0) {
        for (int i = 0; i < a.term(); i++) {
            c.NewTerm(a.tarray_coef(i) * scaler, a.tarray_exp(i));
        }
    }
    return c;
}

// increase the power of the polynomial
Polynomial operator^(const Polynomial& a, const int& expo)
{
    Polynomial c;
    if (a.term() != 0) {
        for (int i = 0; i < a.term(); i++)
            c.NewTerm(a.tarray_coef(i), a.tarray_exp(i) + expo);
    }
    return c;
}

// multiply the two polynomial;
Polynomial operator*(const Polynomial& a, const Polynomial& b)
{
    Polynomial c, temp;
    float coef;
    int exp;
    int aPos;
    for (aPos = 0; aPos < a.term(); aPos++) {
        temp = a.tarray_coef(aPos) * b;
        temp = temp ^ a.tarray_exp(aPos);
        c = c + temp;
    }
    return c;
}

// calculate f(x)
float Polynomial::Eval(float x)
{
    float ans, ansterm;
    int i, j;

    if (x == 0) {
        if (termArray[terms - 1].exp == 0) return termArray[terms - 1].coef;
        else return 0;
    }

    for (i = 0; i < terms; i++) {
        ansterm = 1;
        for (j = 0; j < termArray[i].exp; j++)
            ansterm *= x;
        ansterm *= termArray[i].coef;
        ans += ansterm;
    }
    return ans;
}

Polynomial Polynomial::Mult(Polynomial P)
{
    (*this) = (*this) * P;

    return  *this;
}

istream& operator>>(istream& s, Polynomial& p)
{
    float coef = 0;
    int exp = 0;
    char c;

    s >> c;
    while (c != '/') {
        if (c == '+') {
            s >> coef >> c;
        } else if (c == '-') {
            s >> coef >> c;
            coef *= -1;
        } else {
            s.putback(c);
            s >> coef >> c;
        }

        if (c == 'x') {
            s >> c >> exp >> c;
        } else if (c == '/') {
            exp = 0;
        } else s.clear(ios_base::badbit);   // house keeping
    
        if (s && coef) p.NewTerm(coef, exp);
    }
    return(s);
}

ostream &operator<<(ostream& s, Polynomial const p)
{
    int i;

    for (i = 0; i < p.term(); i++) {
        if (p.tarray_exp(i) != 0) {
            if (p.tarray_coef(i) < 0)
                s << p.tarray_coef(i) << 'x' << '^' << '(' << p.tarray_exp(i) << ')'<< ' ';
            else
                s << "+ " << p.tarray_coef(i) << 'x' << '^' << '(' << p.tarray_exp(i) << ')'<< ' ';
        } else {
            if (p.tarray_coef(i) < 0)
                s << p.tarray_coef(i) << ' ';
            else 
                s << "+ " << p.tarray_coef(i) << ' ';
        }
    }
    // s << '.' << " term: " << p.term() << endl;
    return s;
}

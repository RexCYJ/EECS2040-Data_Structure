#include "Polynomial.h"

Polynomial::Polynomial()
{
    poly.head->data = {0.0, -1};     // initialize the polynomial as 0
}

Polynomial::Polynomial(const Polynomial &a)
{
    if (&a != NULL) {
        *this = a;
    }
}

Polynomial::~Polynomial()
{}

Polynomial& Polynomial::operator+(const Polynomial& b) const
{
    Polynomial *newpoly = new Polynomial;
    Term item;

    Node<Term> *aPos = poly.head->link, 
               *bPos = b.poly.head->link;
    while (aPos != poly.head && bPos != b.poly.head) {
        if (aPos->data.exp == bPos->data.exp) {
            double t = aPos->data.coef + bPos->data.coef;
            item = {t, aPos->data.exp};
            if (t) newpoly->poly.InsertBack(item);
            aPos = aPos->link;
            bPos = bPos->link;
        } else if (aPos->data.exp > bPos->data.exp) {
            item = {aPos->data.coef, aPos->data.exp};
            newpoly->poly.InsertBack(item);
            aPos = aPos->link;
        } else if (aPos->data.exp < bPos->data.exp) {
            item = {bPos->data.coef, bPos->data.exp};
            newpoly->poly.InsertBack(item);
            bPos = bPos->link;
        }
    }

    for (; aPos != poly.head; aPos = aPos->link) {
        item = {aPos->data.coef, aPos->data.exp}; 
        newpoly->poly.InsertBack(item);
    }
    for (; bPos != b.poly.head; bPos = bPos->link) {
        item = {bPos->data.coef, bPos->data.exp};
        newpoly->poly.InsertBack(item);
    }
    return *newpoly;
}

Polynomial& Polynomial::operator-(const Polynomial& b) const
{
    Polynomial *newpoly = new Polynomial;
    Term item;

    Node<Term> *aPos = poly.head->link, 
               *bPos = b.poly.head->link;
    while (aPos != poly.head && bPos != b.poly.head) {
        if (aPos->data.exp == bPos->data.exp) {
            double t = aPos->data.coef - bPos->data.coef;
            item = {t, aPos->data.exp};
            if (t) newpoly->poly.InsertBack(item);
            aPos = aPos->link;
            bPos = bPos->link;
        } else if (aPos->data.exp > bPos->data.exp) {
            item = {aPos->data.coef, aPos->data.exp};
            newpoly->poly.InsertBack(item);
            aPos = aPos->link;
        } else if (aPos->data.exp < bPos->data.exp) {
            item = {(-1) * (bPos->data.coef), bPos->data.exp};
            newpoly->poly.InsertBack(item);
            bPos = bPos->link;
        }
    }

    for (; aPos != poly.head; aPos = aPos->link) {
        item = {aPos->data.coef, aPos->data.exp};
        newpoly->poly.InsertBack(item);
    }
    for (; bPos != b.poly.head; bPos = bPos->link) {
        item = {(-1) * (bPos->data.coef), bPos->data.exp}; 
        newpoly->poly.InsertBack(item);
    }
    return *newpoly;
}

void Polynomial::Multi_coef(const double c)
{
    if (c != 0) {
        Node<Term> *cur = poly.head->link;
        for (; cur != poly.head; cur = cur->link)
            cur->data.coef *= c;
    }
}    

void Polynomial::Multi_exp(const int e)
{
    if (e > 0) {
        Node<Term> *cur = poly.head->link;
        for (; cur != poly.head; cur = cur->link)
            cur->data.exp += e;
    }
}

Polynomial& Polynomial::operator*(const Polynomial& b) const
{
    Polynomial *newpoly = new Polynomial;
    Polynomial *temp = new Polynomial;
    Node<Term> *bPos = b.poly.head->link;

    while (bPos != b.poly.head) {
        *temp = *this;
        temp->Multi_coef(bPos->data.coef);
        temp->Multi_exp(bPos->data.exp);
        *newpoly = *newpoly + *temp;
        bPos = bPos->link;
    }
    return *newpoly;
}

const Polynomial& Polynomial::operator=(const Polynomial& b)
{
    poly = b.poly;
    return *this;
}

double Polynomial::Evaluate(double x) const
{
    double ans = 0, power = 0;
    Node<Term> *cur = poly.head->link;

    while (cur != poly.head) {
        power = 1;
        for (int i = 0; i < cur->data.exp; i++)
            power *= x;
        ans += cur->data.coef * power; 
        cur = cur->link;
    }
    return ans;
}

istream& operator>>(istream& s, Polynomial& a)
{
    int n;
    Term item;

    s >> n;
    if (n > 0)
        while (a.poly.head->link != a.poly.head)
            a.poly.DeleteFront();
    for (int i = 0; i < n; i++) {
        s >> item.coef >> item.exp;
        a.poly.InsertBack(item);
    }    
    
    return s;
}

ostream& operator<<(ostream& s, Polynomial& a)
{
    Node<Term> *cur = a.poly.head->link;

    while (cur != a.poly.head) {
        s << ' ' << cur->data.coef;
        if (cur->data.exp > 1)
            s << "x^" << cur->data.exp;
        else if (cur->data.exp == 1)
            s << 'x';
        s << ' ';
        cur = cur->link;
        if (cur != a.poly.head && cur->data.coef > 0)
            s << '+';
    }
    s << '\n';
    return s;
}
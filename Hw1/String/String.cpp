#include "String.h"

#define STORAGE_INCREMENT   100

String::String(char *init, int m)
{
    int i;
    len = m;
    str = new char[len + 1];              // chars + '\0'
    for (i = 0; init[i] != '\0' && i < len; i++)
        str[i] = init[i];
    str[i] = '\0';
}

bool String::operator==(String s) const
{
    int i = 0;
    while (str[i] == s.str[i] && str[i] != '\0') {
        i++;
    }
    if (str[i] == '\0' && s.str[i] == '\0') return 1;
    else return 0;
}

bool String::operator!() const
{
    if (str[0] == '\0') return 1;
    else return 0;
}

int String::Length() const
{
    int i = 0;
    while (str[i] != '\0') i++;

    return i;
}

// append t to the tail of *this
String String::Concat(const String t)
{
    int i;
    int thislen = Length();
    int tlen = t.Length();
    char null[1] = {'\0'};
    String newstring(null, thislen + tlen);

    for (i = 0; i < thislen; i++)
        newstring.str[i] = str[i];
    for (i = 0; i < tlen; i++)
        newstring.str[thislen + i] = t.str[i];
    newstring.str[newstring.len] = '\0';
    return newstring;
}

// output string from str[start] to str[start + length - 1]
String String::Substr(int start, int length)
{
    if (start + length - 1 >= Length())
        throw "Out of range";
    char null[1] = {'\0'};
    String temp(null, length);
    for (int i = 0; i < length; i++)
        temp.str[i] = str[i + start];
    temp.str[length] = '\0';
    return temp;    
}

// Fast Find: The Knuth-Morris-Patt Algorithm
int String::Find(String pat)
{
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    pat.FailureFunction();
    while ((posP < lengthP) && (posS < lengthS))
        if (pat.str[posP] == str[posS]) {posP++; posS++;}
        else 
            if (posP == 0) posS++;
            else posP = pat.f[posP - 1] + 1;
    if (posP < lengthP) return -1;
    else return posS - lengthP;
}

void String::FailureFunction()
{
    int lengthP = Length();
    f = new int[Length()];
    f[0] = -1;
    for (int j = 1; j < lengthP; j++) {
        int i = f[j - 1];
        while ((*(str + j) != *(str + i + 1)) && (i >= 0)) i = f[i];
        if (*(str + j) == *(str + i + 1))
            f[j] = i + 1;
        else f[j] = -1;
    }
}

// Delete(start, length)
String String::Delete(int start, int length)
{
    int charlen = Length();
    if (start + length - 1 >= charlen)
        throw "Out of range";
    char *temp = new char[charlen - length + 1];
    int i;
    for (i = 0; i < start; i++) temp[i] = str[i];
    for (; i < len - length; i++) temp[i] = str[i + length];
    temp[i] = '\0';
    delete [] str;
    str = temp;
    len = charlen - length;
    return *this;
}

String String::CharDelete(char c) 
{
    char *temp = new char[len];
    int cursor = 0, charlen = Length();
    for (int i = 0; i < charlen; i++)
        if (str[i] != c) 
            temp[cursor++] = str[i];
    temp[cursor] = '\0';
    delete [] str;
    str = temp;
    return *this;
}

istream& operator>>(istream &s, String &instr)
{
    int inputlen = 0, storage = STORAGE_INCREMENT;
    char c;
    char *strbuf = new char[storage];
    
    s.get(c);
    while (c == '\n') s.get(c);         // newline filter 
    while (c != '\n') {
        strbuf[inputlen++] = c;
        if (inputlen == storage) {
            storage += STORAGE_INCREMENT;
            char *temp = new char[storage];
            for (int j = 0; j < inputlen; j++)
                temp[j] = strbuf[j];
            delete [] strbuf;
            strbuf = temp;
        }
        s.get(c);
    }
    strbuf[inputlen] = '\0';
    delete [] instr.str;
    instr.str = new char[inputlen + 1];
    for (int j = 0; j <= inputlen; j++)
        instr.str[j] = strbuf[j];
    instr.len = inputlen;
    delete [] strbuf;    

    return s;
}

ostream& operator<<(ostream &s, const String &outstr)
{
    for (int i = 0; outstr.str[i] != '\0'; i++)
        s << outstr.str[i];
    s << endl;

    return s;
}
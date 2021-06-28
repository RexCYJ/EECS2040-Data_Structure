#ifndef HASHING_H
#define HASHING_H

#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
#include <list>

using std::pair;
using std::list;
using std::string;
using std::ostream;

int h(const string &);					// hashfunction

class SymbolTable1			// probing
{
	friend ostream& operator<<(ostream&, const SymbolTable1&);
	public:
		SymbolTable1();
		int Insert(pair<string, int> &);
		pair<string, int>* Search(const string &);
	private:
		pair<string, int>* ht[26];
};

class SymbolTable2			// chaining
{
	friend ostream& operator<<(ostream&, SymbolTable2&);
	public:
		SymbolTable2();
		int Insert(pair<string, int> &);
		pair<string, int>* Search(const string &);
	private:
		list<pair<string, int>> ht[26];
};

ostream& operator<<(ostream&, const SymbolTable1&);
ostream& operator<<(ostream&, SymbolTable2&);

#include "Hashing.cpp"

#endif
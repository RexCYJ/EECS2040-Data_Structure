#include "Hashing.h"

using std::cout;

int h(const string &s) {return s.at(0) - 'a';}

SymbolTable1::SymbolTable1()
{
	for (int i = 0; i < 26; i++)
		ht[i] = NULL;
}

int SymbolTable1::Insert(pair<string, int> &p)
{
	int i = h(p.first);
	int j;
	for (j = i; ht[j] && ht[j]->first != p.first;) {
		j = (j + 1) % 26;
		if (i == j) return -1;
	}
	if (ht[j] == NULL) {
		ht[j] = new pair<string, int>;
		ht[j]->first = p.first; ht[j]->second = p.second; 
		return j;
	} else if (ht[j]->first == p.first) {
		ht[j]->second = p.second; 
		return j;
	}
	return -1;
}

pair<string, int>* SymbolTable1::Search(const string &s)
{
	int i = h(s);
	int j;
	for (j = i; ht[j] && ht[j]->first != s;) {
		j = (j + 1) % 26;
		if (j == i) return 0;
	}
	if (ht[j] == NULL) return 0;
	return ht[j];
}


SymbolTable2::SymbolTable2()
{

}

int SymbolTable2::Insert(pair<string, int> &p)
{
	int i = h(p.first);
	list<pair<string, int>>::iterator cur;
	for (cur = ht[i].begin(); cur != ht[i].end(); cur++)
		if (cur->first == p.first) {cur->second = p.second; return i;}
	ht[i].push_back(p);
	return i;
}

pair<string, int>* SymbolTable2::Search(const string &s)
{
	int i = h(s);
	pair<string, int> p;
	list<pair<string, int>>::iterator cur;
	for (cur = ht[i].begin(); cur != ht[i].end(); cur++)
		if (cur->first == s)
			return &(*cur);
	return 0;
}

ostream& operator<<(ostream& os, const SymbolTable1& a)
{
	for (int i = 0; i < 26; i++) {
		if (a.ht[i] != NULL)
			os << "ht[" << i << "] -> (" << a.ht[i]->first << ", " << a.ht[i]->second << ")\n";
	}
	return os;
}

ostream& operator<<(ostream& os, SymbolTable2& a)
{
	list<pair<string, int>>::iterator cur;
	for (int i = 0; i < 26; i++) {
		if (!a.ht[i].empty()) {
			os << "ht[" << i << "]";
			for (cur = a.ht[i].begin(); cur != a.ht[i].end(); cur++)
				os << " -> (" << cur->first << ", " << cur->second << ")";
			os << '\n';
		}
	}
	return os;
}

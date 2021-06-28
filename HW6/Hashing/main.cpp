#include "Hashing.h"

using std::cout;
using std::endl;
using std::setw;

void search_display1(string &, SymbolTable1 &);
void search_display2(string &, SymbolTable2 &);

int main(void)
{
	cout << "<Probing Hash table>\n";
	cout << "Set up ten objects\n";
	SymbolTable1 hash1;
	pair<string, int> p1("jjliou", 926);
	pair<string, int> p2("bschen", 910);
	pair<string, int> p3("chlien", 851);
	pair<string, int> p4("cschang", 932);
	pair<string, int> p5("ccchao", 863);
	pair<string, int> p6("ychuang", 856);
	pair<string, int> p7("sclu", 806);
	pair<string, int> p8("ywhong", 815);
	pair<string, int> p9("tljong", 938);
	pair<string, int> p10("mlli", 827);
	cout << "Insert the ten objects\n";
	hash1.Insert(p1);
	hash1.Insert(p2);
	hash1.Insert(p3);
	hash1.Insert(p4);
	hash1.Insert(p5);
	hash1.Insert(p6);
	hash1.Insert(p7);
	hash1.Insert(p8);
	hash1.Insert(p9);
	hash1.Insert(p10);
	cout << hash1;

	cout << "Search for keys\n";
	string key = "mcchang";
	search_display1(key, hash1);
	key = "tljong";
	search_display1(key, hash1);
	key = "ychung";
	search_display1(key, hash1);
	key = "ccchao";
	search_display1(key, hash1);
	key = "ywhong";
	search_display1(key, hash1);

	cout << endl;
	cout << "<Chaining Hash table>\n";

	SymbolTable2 hash2;
	cout << "Insert the ten objects\n";
	hash2.Insert(p1);
	hash2.Insert(p2);
	hash2.Insert(p3);
	hash2.Insert(p4);
	hash2.Insert(p5);
	hash2.Insert(p6);
	hash2.Insert(p7);
	hash2.Insert(p8);
	hash2.Insert(p9);
	hash2.Insert(p10);
	cout << hash2;

	cout << "Search for keys\n";
	key = "mcchang";
	search_display2(key, hash2);
	key = "tljong";
	search_display2(key, hash2);
	key = "ychung";
	search_display2(key, hash2);
	key = "ccchao";
	search_display2(key, hash2);
	key = "ywhong";
	search_display2(key, hash2);

	return 0;	
}

void search_display1(string &key, SymbolTable1 &hash1)
{
	pair<string, int> *data;
	data = hash1.Search(key);
	cout << "Search key: " << setw(8) << key;
	if (data == NULL) {cout << "  Result:  Not Found\n";}
	else {cout << "  Result:  (" << data->first << ", " << data->second << ")\n";}
}

void search_display2(string &key, SymbolTable2 &hash2)
{
	pair<string, int> *data;
	data = hash2.Search(key);
	cout << "Search key: " << setw(8) << key;
	if (data == NULL) {cout << "  Result:  Not Found\n";}
	else {cout << "  Result:  (" << data->first << ", " << data->second << ")\n";}
}

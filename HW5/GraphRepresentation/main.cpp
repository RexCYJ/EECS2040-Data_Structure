#include "Graph.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

int main(void) 
{
	Graph g1(8), g2(8), g3(10);

    ifstream in("input.txt");
    ofstream out("output.txt");
    auto cin_buf = cin.rdbuf(in.rdbuf());
    auto cout_buf = cout.rdbuf(out.rdbuf());

	// --------------- Graph 1 ----------------
	cout << "Input the graph 1:\n";
	cin >> g1;
	cout << "Your Input:\n" <<	g1 << endl;
	
	// BFS
	cout << "g1.BFS(0): "; g1.BFS(0);
	cout << "g1.BFS(3): "; g1.BFS(3);
	cout << "g1.BFS(7): "; g1.BFS(7);

	// DFS
	cout << "g1.DFS(0): "; g1.DFS(0);
	cout << "g1.DFS(3): "; g1.DFS(3);
	cout << "g1.DFS(7): "; g1.DFS(7);

	// Components & DfnLow
	g1.Components();
	g1.DfnLow(3);

	 
	// --------------- Graph 2 ----------------
	cout << "\nInput the graph 2:\n";
	cin >> g2;
	cout << "Your Input:\n" <<	g2 << endl;
	
	// BFS
	cout << "g2.BFS(0): "; g2.BFS(0);
	cout << "g2.BFS(3): "; g2.BFS(3);
	cout << "g2.BFS(7): "; g2.BFS(7);

	// DFS
	cout << "g2.DFS(0): "; g2.DFS(0);
	cout << "g2.DFS(3): "; g2.DFS(3);
	cout << "g2.DFS(7): "; g2.DFS(7);

	// Components & DfnLow
	g2.Components();
	g2.DfnLow(3);

	// --------------- Graph 3 ----------------
	cout << "\nInput the graph 3:\n";
	cin >> g3;
	cout << "Your Input:\n" <<	g3 << endl;
	
	// BFS
	cout << "g3.BFS(0): "; g3.BFS(0);
	cout << "g3.BFS(3): "; g3.BFS(3);
	cout << "g3.BFS(7): "; g3.BFS(7);

	// DFS
	cout << "g3.DFS(0): "; g3.DFS(0);
	cout << "g3.DFS(3): "; g3.DFS(3);
	cout << "g3.DFS(7): "; g3.DFS(7);

	// Components & DfnLow
	g3.Components();
	g3.DfnLow(3);


    cin.rdbuf(cin_buf);
    cout.rdbuf(cout_buf);

	return 0;
}
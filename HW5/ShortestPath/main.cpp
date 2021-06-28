#include "ShortestPath.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cin;

int main(void)
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    auto cin_buf = cin.rdbuf(in.rdbuf());
    auto cout_buf = cout.rdbuf(out.rdbuf());
	
	Graph G1;
	cout << "\nInput the graph:\n";
	cin >> G1;
	cout << "G1:\n" << G1 << endl;
	G1.Dijkstra(4);
	cout << "\nInput the graph:\n";
	cin >> G1;
	cout << "G1':\n" << G1 << endl;
	G1.Dijkstra(0);
	cout << "\nInput the graph:\n";
	cin >> G1;
	cout << "G1'':\n" << G1 << endl;
	G1.Dijkstra(0);

	cout << "\n===============================================================\n";

	Graph G2;
	cout << "\nInput the graph:\n";
	cin >> G2;
	cout << "G2:\n" << G2 << endl;
	G2.BellmanFord(0);
	cout << "\nInput the graph:\n";
	cin >> G2;
	cout << "G2':\n" << G2 << endl;
	G2.BellmanFord(0);

	cout << "\n===============================================================\n";
	
	Graph G3;
	cout << "\nInput the graph:\n";
	cin >> G3;
	cout << "G3:\n" << G3 << endl;
	G3.Floyd();
	cout << "\nInput the graph:\n";
	cin >> G3;
	cout << "G2:\n" << G3 << endl;
	G3.Floyd();

    cin.rdbuf(cin_buf);
    cout.rdbuf(cout_buf);

	return 0;
}
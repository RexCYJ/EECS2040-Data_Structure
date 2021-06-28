#ifndef SHORTEST_PATH
#define SHORTEST_PATH

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class Graph
{
	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, Graph&);
	public:
		Graph(int);
		
		// Single source / all destination nonnegative weights
		void Dijkstra(const int);

		// Single source / all destination negative weights DAG
		void BellmanFord(const int);

		// All pairs DAG shortest paths
		void Floyd();

	private:
		int n;
		int **edge;
};

istream& operator>>(istream&, Graph&);
ostream& operator<<(ostream&, Graph&);

#include "ShortestPath.cpp"

#endif
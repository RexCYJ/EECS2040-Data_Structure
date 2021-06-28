#ifndef GRAPH_REPRESENTATION
#define GRAPH_REPRESENTATION

#include <iostream>
#include <list>
#include <vector>
#include <queue>

using std::istream;
using std::ostream;
using std::endl;
using std::cin;
using std::cout;
using std::list;
using std::vector;
using std::queue;

// The number of vertice is fixed after constructed.
// This class is for undirected graph.
class Graph {
	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, Graph&);
	public:
		Graph(int);
	
		void AddEdge(int, int);

		void DFS(const int);
		void BFS(const int);
		void Components();
		void DfnLow(const int);

	private:
		void DFSrec(const int);
		void DfnLowrec(const int, const int);
		int num;
		int vertice;			// number of vertice
		int *dfn;				// store the depth-first order of each vertex
		int *low;				// store the low of each vertex
		int *traverse;			// store the travesal order
		bool *visited;			// used to check whether the vertex has been visited
		vector<list<int>> vertex;	// adjacency lists array, vertice are indexed from 0 to n-1.
};

istream& operator>>(istream&, Graph&);
ostream& operator<<(ostream&, Graph&);

#include "Graph.cpp"

#endif
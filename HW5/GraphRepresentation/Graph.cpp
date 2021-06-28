#include "Graph.h"

Graph::Graph(int n = 0): vertice(n), vertex(n)
{
	// vector<list<int>> vertex(vertice, list<int>());
}

void Graph::AddEdge(int a, int b)
{
	if (a < 0 || a >= vertice)	throw "Wrong index";
	if (b < 0 || b >= vertice)	throw "Wrong index";

	vertex.at(a).push_back(b);
	vertex.at(b).push_back(a);
}

void Graph::DFS(const int root)			// Driver
{
	visited = new bool[vertice];
	for (int i = 0; i < vertice; i++)
		visited[i] = false;
	// cout << "( ";
	DFSrec(root);
	cout << '\n';
	delete[] visited;
}

void Graph::DFSrec(const int root)		// Runner
{
	visited[root] = true;
	cout << root << " ";
	list<int>::iterator cur = vertex.at(root).begin();
	int next = *cur;
	while (1) {
		if (!visited[next]) {
			// cout << "( ";
			DFSrec(next);
		}
		cur++;
		if (cur != vertex.at(root).end()) 
			next = *cur;
		else {
			// cout << ')';
			return;
		}
	}
}

void Graph::BFS(const int v)
{
	visited = new bool[vertice];
	for (int i = 0; i < vertice; i++) visited[i] = false;
	visited[v] = true;
	cout << v << ' ';

	queue<int> q;
	q.push(v);
	
	int cur;				// current vertex
	list<int>::iterator w;	// the vertex adjacent to cur

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (w = vertex.at(cur).begin(); w != vertex.at(cur).end(); w++) {
			if (!visited[*w]) {
				q.push(*w);
				visited[*w] = true;
				cout << *w << ' ';
			}
		}
	}
	cout << '\n';
	delete[] visited;
}

void Graph::Components()
{
	int j = 1;
	visited = new bool[vertice];
	for (int i = 0; i < vertice; i++) visited[i] = false;
	for (int i = 0; i < vertice; i++)
		if (!visited[i]) {
			cout << "Component " << j++ << ": ";
			DFSrec(i);			// find a component containing i
			cout << endl;
		}
	delete [] visited;
}

void Graph::DfnLow(const int x)
{
	num = 1;
	dfn = new int [vertice];
	low = new int [vertice];
	for (int i = 0; i < vertice; i++) dfn[i] = 0;
	for (int i = 0; i < vertice; i++) low[i] = 0;
	DfnLowrec(x, -1);
	cout << "dfn[] and low[]: \n";
	cout << " index: ";
	for (int i = 0; i < vertice; i++) cout << i << ' ';	cout << endl << " dfn[]: ";
	for (int i = 0; i < vertice; i++) cout << dfn[i] << ' '; cout << endl << " low[]: ";
	for (int i = 0; i < vertice; i++) cout << low[i] << ' '; cout << endl;
	delete[] dfn;
	delete[] low;
}

inline int min(int a, int b) {return (a > b)? b: a;}

void Graph::DfnLowrec(const int u, const int v)
{
	dfn[u] = low[u] = num++;		// setting dfn
	list<int>::iterator adjVX;
	for (adjVX = vertex.at(u).begin(); adjVX != vertex.at(u).end(); adjVX++)
		if (dfn[*adjVX] == 0) {					// haven't visit
			DfnLowrec(*adjVX, u);
			low[u] = min(low[u], low[*adjVX]);
		} else if (*adjVX != v) 
			low[u] = min(low[u], dfn[*adjVX]);
}

istream& operator>>(istream& is, Graph& g)
{
	int a, b;

	is >> a >> b;
	while (a != -1) {
		g.AddEdge(a, b);
		is >> a >> b;
	}

	return is;
}

ostream& operator<<(ostream& os, Graph& g)
{
	vector<list<int>>::iterator cur = g.vertex.begin();
	list<int>::iterator listcur = cur->begin();
	int i;

	for (cur, i = 0; cur != g.vertex.end(); cur++, i++) {
		os << "  Vertex " << i << ": ";
		for (listcur = cur->begin(); listcur != cur->end(); listcur++) {
			os << *listcur << ' ';
		}
		os << endl;
	}

	return os;
}
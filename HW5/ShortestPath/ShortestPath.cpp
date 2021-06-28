#include "ShortestPath.h"
#include <deque>

#define INF	999999999

using std::deque;

Graph::Graph(int vertice = 0): n(vertice) {}

void Graph::Dijkstra(const int v)
{
	int *s = new int [n];
	int *dist = new int [n];
	for (int i = 0; i < n; i++) {
		s[i] = false;
		dist[i] = edge[v][i];
	}
	int u;			// the vertex that is not in S
	int w;			// u's pre-vertex
	int mindist;
	deque<int> *path = new deque<int> [n];
	path[v].push_back(v);

	// Column header
	cout << "  Iter  vertex | ";
	for (int i = 0; i < n; i++)
		cout << std::setw(5) << "[" << i << ']';
	cout << endl;

	int *Setv = new int [n], setv;
	for (int i = 0; i < n; i++)	Setv[i] = -1;
	Setv[0] = v;

	s[v] = true;
	dist[v] = 0;
	for (int i = 0; i < n - 1; i++) {					// n - 1 shortest path from v
		u = v; mindist = INF;
		for (int j = 0; Setv[j] != -1; j++) {					// search the vertice in s
			// if (s[j]) {									// from the vertex in set s
				setv = Setv[j];
				for (int k = 0; k < n; k++) {			// Check its adjacent out-edge
					if (edge[setv][k] != INF && !s[k]) {
						if (dist[setv] + edge[setv][k] < mindist)	{	// update dist
							mindist = dist[setv] + edge[setv][k];
							u = k; w = setv;
						}
						if (dist[k] > dist[setv] + edge[setv][k])
							dist[k] = dist[setv] + edge[setv][k];
					}
				}	// for 3
			// }
		}	// for 2
		if (u == v) break;
		s[u] = true;
		dist[u] = mindist;
		path[u] = path[w];
		path[u].push_back(u);
		Setv[i + 1] = u;
		// Output row
		cout << '>' << std::setw(5) << i << std::setw(8) << u << " | ";
		for (int j = 0; j < n; j++) {
			if (dist[j] >= INF) cout << std::setw(7) << "-";
			else cout << std::setw(7) << dist[j];
		}
		cout << endl;
	}	// for 1
	cout << "\n Path   length     vertice on the path\n";
	for (int i = 0; i < n; i++) {
		cout << "<"<< v << ',' << i << ">";
		if (dist[i] == INF) cout << std::setw(9) << "-" << "   ";
		else cout << std::setw(9) << dist[i] << "   ";
		while (!path[i].empty()) {
			cout << std::setw(3) << path[i].front();
			path[i].pop_front();
		}
		cout << endl;
	}
	delete [] path;
	delete [] dist;
	delete [] s;
}

void Graph::BellmanFord(const int v)
{
	int *dist = new int [n];
	bool *visited = new bool [n];
	for (int i = 0; i < n; i++) {
		dist[i] = edge[v][i];
		if (edge[v][i] == INF)  visited[i] = false;
		else visited[i] = true;
	}
	dist[v] = 0;
	visited[v] = true;
	cout << std::setw(15) << "dist\n" << "   k | ";
	for (int i = 0; i < n; i++)
		cout << "   "<< '[' << i << ']';
	cout << endl;
	
	for (int k = 2; k < n; k++) {					// dist(2)[] ~ dist(n-1)[]
		cout << std::setw(4) << k << ' ' << '|';
		for (int u = 0; u < n; u++) {
			if (u != v) 							// for all u not v
				for (int i = 0; i < n; i++)
					if (visited[i] && edge[i][u] != INF) {
						if (dist[u] > dist[i] + edge[i][u])
							dist[u] = dist[i] + edge[i][u];
						visited[u] = true;
					} 
			if (dist[u] == INF) cout << std::setw(6) << "-";
			else cout << std::setw(6) << dist[u];
		}
		cout << endl;
	}
	delete [] dist;
	delete [] visited;
}

void Graph::Floyd()
{
	int **a = new int* [n];
	int **kay = new int* [n];
	
	for (int i = 0; i < n; i++) {
		a[i] = new int [n];
		kay[i] = new int [n];
		for (int j = 0; j < n; j++) {
			if (i == j) a[i][j] = 0;
			else a[i][j] = edge[i][j];
			kay[i][j] = -1;
		}
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (a[i][k] != INF && a[k][j] != INF && (a[i][j] > (a[i][k] + a[k][j])))
					{kay[i][j] = k; a[i][j] = a[i][k] + a[k][j];}
	
	cout << "a[i][j]" << std::setw(4*n+15) << "kay[i][j]" << endl;

	cout << "   j \\ i";
	for (int i = 0; i < n; i++)
		cout << std::setw(4) << i;
	cout << "       ";	
	cout << "   j \\ i";
	for (int i = 0; i < n; i++)
		cout << std::setw(4) << i;
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << std::setw(4) << i << "  | ";
		for (int j = 0; j < n; j++)
			if (a[i][j] == INF) cout << std::setw(4) << " ";
			else if (i == j)	cout << std::setw(4) << 0;
			else cout << std::setw(4) << a[i][j];
		
		cout << "       ";
		cout << std::setw(4) << i << "  | ";
		for (int j = 0; j < n; j++)
			if (a[i][j] == INF) cout << std::setw(4) << " ";
			else if (kay[i][j] == -1) cout << std::setw(4) << "-";
			else cout << std::setw(4) << kay[i][j];
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		delete [] a[i];	
		delete [] kay[i];
	}
	delete [] a;
	delete [] kay;
}

istream& operator>>(istream& is, Graph& g)
{
	if (g.n != 0) {
		for (int i = 0; i < g.n; i++)
			delete [] g.edge[i];
		delete [] g.edge;
	}

	int n;
	is >> n;
	g.n = n;
	g.edge = new int* [n];
	for (int i = 0; i < n; i++) { 		// initialization
		g.edge[i] = new int [n];
		for (int j = 0; j < n; j++)
			g.edge[i][j] = INF;
	}
	
	int u, v, weight;
	is >> u >> v >> weight;
	while (u != -1) {
		if (u > n || v > n) throw "Wrong index";
		g.edge[u][v] = weight;
		is >> u >> v >> weight;
	}

	return is;
}

ostream& operator<<(ostream& os, Graph& g)
{
	os << "      ";
	for (int i = 0; i < g.n; i++)
		os << std::setw(5) << i;
	os << endl;
	for (int i = 0; i < g.n; i++) {
		os << std::internal << std::setw(5) << i << ' ';
		for (int j = 0; j < g.n; j++)
			if (g.edge[i][j] == INF) 
				os << std::right << std::setw(5) << "-";
			else
				os << std::right << std::setw(5) << g.edge[i][j];
		os << endl;
	}
	
	return os;
}
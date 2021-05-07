#include <iostream>
#include <fstream>
#include "maze.h"

using namespace std;
using std::cin;
using std::cout;
// int **maze, **mark;

int main(void)
{
    ifstream in("in.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
    
    int m = 0, p = 0, mappoint;
    int i, j;

    Move[N]  = {-1, 0};
    Move[NE] = {-1, 1};
    Move[E]  = {0, 1};
    Move[SE] = {1, 1};
    Move[S]  = {1, 0};
    Move[SW] = {1, -1};
    Move[W]  = {0, -1}; 
    Move[NW] = {-1, -1}; 

    cin >> m >> p;                  // read matrix size
    while ((m > 0) && (p > 0)) {
        cout << "\n\nreading maze matrix\n";
        maze = new int*[m + 2];
        mark = new int*[m + 2];
        maze[0] = new int[p + 2];
        maze[m + 1] = new int[p + 2];
        mark[0] = new int[p + 2];
        mark[m + 1] = new int[p + 2];

        for (i = 0; i < p + 2; i++) 
            maze[0][i] = maze[m + 1][i] = mark[0][i] = mark[m + 1][i] = 1; 
        
        for (i = 1; i <= m; i++) {
            maze[i] = new int[p + 2];
            mark[i] = new int[p + 2];
            mark[i][0] = mark[i][p + 1] = 0;
            maze[i][0] = maze[i][p + 1] = 1;
            for (j = 1; j <= p; j++) {
                cin >> mappoint;
                mark[i][j] = 0;
                maze[i][j] = mappoint;
            }
        }       
        cout << endl;
        for (i = 0; i < m + 2; i++) {
            for (j = 0; j < p + 2; j++) {
                if ((maze[i][j] || mark[i][j])) cout << "%%";
                else cout << "  ";
            } 
            cout << endl;
        }
        
        cout << "\nstart searching\n";
        Path(m, p);
        
        for (i = 0; i < m + 2; i++) {
            delete [] maze[i];
            delete [] mark[i];
        }
        delete [] maze;
        delete [] mark;
        cin >> m >> p;
    }
    
    cin.rdbuf(cinbuf);

    return 0;
}
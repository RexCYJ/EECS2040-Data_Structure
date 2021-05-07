#ifndef MAZE_PATHFINDER
#define MAZE_PATHFINDER

#include <iostream>
using namespace std;

int **maze, **mark;

typedef struct offsets {
    int di, dj;
} Offsets;

enum directions {N, NE, E, SE, S, SW, W, NW};
char dir_name[16] = {' ', 'N', 'N', 'E', ' ', 'E', 'S', 'E', ' ', 'S',
                     'S', 'W', ' ', 'W', 'N', 'W'};

Offsets Move[8];

typedef struct item {
    int x;
    int y;
    int dir;
} Item;

class Stack 
{
    private:
        Item* stack;
        int top;
        int capacity;
    public:
        Stack(int stackCapacity = 10);
        bool IsEmpty() const;
        Item& Top() const;
        void Push(const Item&);
        void Pop();
    friend ostream& operator<<(ostream& os, Stack& s);
};

Stack::Stack(int stackCapacity)
{
    if (stackCapacity < 1) throw "Capacity less than 1";
    stack = new Item[stackCapacity];
    capacity = stackCapacity;
    top = -1;
}

inline bool Stack::IsEmpty() const {return top == -1;}

Item& Stack::Top() const {return stack[top];}

void Stack::Push(const Item& t)
{
    if (top + 1 == capacity) {
        Item* temp = new Item[2 * capacity];
        copy(stack, stack + capacity, temp);
        capacity = 2 * capacity;
        delete [] stack;
        stack = temp;
    }
    stack[++top] = t;
}

void Stack::Pop()
{
    stack[top--] = {0, 0, 0};
}

void Path(const int m, const int p)
{
    mark[1][1] = 1;
    Stack stack;
    Item temp = {1, 1, NE};
    stack.Push(temp);
    while (!stack.IsEmpty()) {
        temp = stack.Top();
        stack.Pop();
        cout << "\n\n Current path:" << stack;
        int i = temp.x; int j = temp.y; int d = temp.dir + 1;
        while (d < 8) {
            printf("\n @ Pos(%2d, %2d)   Dir: %c%c", i, j, 
                            dir_name[d*2], dir_name[d*2 + 1]);
            int g = i + Move[d].di; int h = j + Move[d].dj;
            if ((g == m) && (h == p) && !maze[m][p]) {
                stack.Push({i, j, d});
                cout << "\n The Way To The Destination:";
                cout << stack;
                cout << "Destination: (" << m << ", " << p << ") \n";
                return;
            } 
            if ((!maze[g][h]) && (!mark[g][h])) {
                mark[g][h] = 1;
                temp.x = i; temp.y = j; temp.dir = d;
                stack.Push(temp);
                i = g; j = h; d = N;
            } else 
                d++;
        }
        cout << "\nback to previous point."; 
    }
    cout << "\n\nNo path in maze." << endl;
}

ostream& operator<<(ostream& os, Item& items)
{
    return os << '(' << items.x << ", " << items.y << ", " << items.dir << ')';
}

ostream& operator<<(ostream& os, Stack& s)
{
    if (s.IsEmpty()) return os << "\n  At starting point\n";
    for (int i = 0; i <= s.top; i++) {
        if (i % 5 == 0) printf("\n  ");
        printf(" %-2d: (%2d, %2d, %c%c) -> ", i, s.stack[i].x, s.stack[i].y, dir_name[(s.stack[i].dir)*2], dir_name[(s.stack[i].dir)*2 + 1]);
    }
    return os << endl;
}

#endif
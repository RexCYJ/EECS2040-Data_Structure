#include <iostream>
#include "Queue.h"

using namespace std;
// using std::cin;
// using std::cout;

int main(void)
{
    Queue<int> A(10);
    Queue<int> B(5);
    char c; 
    int input;

    B.Push(1000);
    B.Push(2000);
    B.Push(3000);
    B.Push(4000);

    cout << "Type your instructions below.\n";
    cout << "e: exit\t\t\tf: return front\t\tr: return rear\t\tc: return capacity\n";
    cout << "s: return size\t\tp: push a number\tP: pop the front\tm: merge\n";
    cout << "d: display the queue\n\n>> Your instruction: ";

    cin >> c;
    while (c != 'e') {
        switch (c) {
            case 'f':
                cout << "\tthe front of queue A is    " << A.Front() << endl;
                break;
            case 'r':
                cout << "\tthe rear of queue A is     " << A.Rear() << endl;
                break;
            case 'c':
                cout << "\tthe capacity of queue A is " << A.Get_capacity() << endl;
                break;
            case 's':
                cout << "\tthe size of queue A is     " << A.Get_size() << endl;
                break;
            case 'p':
                cin >> input;
                A.Push(input);
                cout << "\tpush " << input << " into queue A\n";
                break;
            case 'P':
                cout << "\tpop out " << A.Front() << "\n";
                A.Pop();
                break;
            case 'm':
                cout << "\tmerge A with B(1000, 2000, 3000, 4000)\n";
                cout << "\tthe result:\n" << A.merge(B);
                break;
            case 'd':
                cout << A;
                break;
            default:
                cout << "\tWarning: Invalid input!\n";
                break;
        }
        cout << "\n>> Your instruction: ";
        cin >> c;
    }
    
    return 0;
}
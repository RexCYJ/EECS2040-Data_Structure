// Deque demo

#include <iostream>
#include "Bag.h"

using namespace std;

int main(void)
{
    Deque<int> deque_int(10);
    Deque<float> deque_float(10);
    char in;
    int input;
    float inputf;

    cout << "\n<Deque Function Demonstration> Type: int\n";
    cout << "Munipulate two deques by the following instructions:\n";
    cout << " E: exit, \t\ts: object size, \tc: object capacity, \td: display deque, \tr: rear element, \n";
    cout << " f: front element, \tP: push front, \t\tp: pop front, \t\ti: inject rear, \te: eject rear\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'E') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << deque_int.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << deque_int.Size() << endl;
                break;
            case 'r':
                cout << "   Rear: " << deque_int.Rear() << endl;
                break;
            case 'f':
                cout << "   Front: " << deque_int.Front() << endl;
                break;
            case 'P':
                cin >> input;
                deque_int.Push(input);
                cout << "   Push " << input << endl;
                cout << deque_int;
                break;
            case 'p':
                cout << "   Pop: " << deque_int.Front() << endl;
                deque_int.Pop();
                cout << deque_int;
                break;
            case 'i':
                cin >> input;
                deque_int.Inject(input);
                cout << "   Inject " << input << endl;
                cout << deque_int;
                break;
            case 'e':
                cout << "   Eject: " << deque_int.Rear() << endl;
                deque_int.Eject();
                cout << deque_int;
                break;
            case 'd':
                cout << deque_int;
                break;
            default:
                cout << "\tWarning: Invalid input!\n";
                break;
        }
        cout << "\n>> ";
        cin >> in;
    }

    cout << "\n<Deque Function Demonstration> Type: float\n";
    cout << "Munipulate two deques by the following instructions:\n";
    cout << " E: exit, \t\ts: object size, \tc: object capacity, \td: display deque, \tr: rear element, \n";
    cout << " f: front element, \tP: push front, \t\tp: pop front, \ti: inject rear, \te: eject rear\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'E') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << deque_float.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << deque_float.Size() << endl;
                break;
            case 'b':
                cout << "   Bottom: " << deque_float.Element() << endl;
                break;
            case 'r':
                cout << "   Rear: " << deque_float.Rear() << endl;
                break;
            case 'f':
                cout << "   Front: " << deque_float.Front() << endl;
                break;
            case 'P':
                cin >> inputf;
                deque_float.Push(inputf);
                cout << "   Push " << inputf << endl;
                cout << deque_float;
                break;
            case 'p':
                cout << "   Pop: " << deque_float.Front() << endl;
                deque_float.Pop();
                cout << deque_float;
                break;
            case 'i':
                cin >> inputf;
                deque_float.Inject(inputf);
                cout << "   Inject " << inputf << endl;
                cout << deque_float;
                break;
            case 'e':
                cout << "   Eject: " << deque_float.Rear() << endl;
                deque_float.Eject();
                cout << deque_float;
                break;
            case 'd':
                cout << deque_float;
                break;
            default:
                cout << "\tWarning: Invalid input!\n";
                break;
        }
        cout << "\n>> ";
        cin >> in;
    }
    
    return 0;
}
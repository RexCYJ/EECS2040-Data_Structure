// Queue demo file

#include <iostream>
#include "Bag.h"

using namespace std;

int main(void)
{
    Queue<int> queue_int(10);
    Queue<char> queue_char(10);
    char in;
    int input;
    char inputf;

    cout << "\n<Queue Function Demonstration> Type: int\n";
    cout << "Munipulate two queues by the following instructions:\n";
    cout << " e: exit, \t\ts: object size, \tc: object capacity, \td: display queue, \n f: front element, \tr: rear element, \tP: push input, \t\tp: pop\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'e') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << queue_int.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << queue_int.Size() << endl;
                break;
            case 'f':
                cout << "   Front: " << queue_int.Front() << endl;
                break;
            case 'r':
                cout << "   Rear: " << queue_int.Rear() << endl;
                break;
            case 'P':
                cin >> input;
                queue_int.Push(input);
                cout << "   Push " << input << endl;
                cout << queue_int;
                break;
            case 'p':
                cout << "   Pop " << queue_int.Front() << endl;
                queue_int.Pop();
                cout << queue_int;
                break;
            case 'd':
                cout << queue_int;
                break;
            default:
                cout << "\tWarning: Invalid input!\n";
                break;
        }
        cout << "\n>> ";
        cin >> in;
    }

    cout << "\n<Queue Function Demonstration> Type: char\n";
    cout << "Munipulate two queues by the following instructions:\n";
    cout << " e: exit, \t\ts: object size, \tc: object capacity, \td: display queue, \n f: front element, \tr: rear element, \tP: push input, \t\tp: pop\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'e') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << queue_char.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << queue_char.Size() << endl;
                break;
            case 'f':
                cout << "   Front: " << queue_char.Front() << endl;
                break;
            case 'r':
                cout << "   Rear: " << queue_char.Rear() << endl;
                break;
            case 'P':
                cin >> inputf;
                queue_char.Push(inputf);
                cout << "   Push " << inputf << endl;
                cout << queue_char;
                break;
            case 'p':
                cout << "   Pop " << queue_char.Front() << endl;
                queue_char.Pop();
                cout << queue_char;
                break;
            case 'd':
                cout << queue_char;
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
// Stack demo file

#include <iostream>
#include "Bag.h"

using namespace std;

int main(void)
{
    Stack<int> stack_int(10);
    Stack<float> stack_float(10);
    char in;
    int input;
    float inputf;

    cout << "\n<Stack Function Demonstration> Type: int\n";
    cout << "Munipulate two stacks by the following instructions:\n";
    cout << " e: exit, \t\ts: object size, \tc: object capacity, \td: display stack, \n b: bottom element, \tP: push input, \t\tp: pop\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'e') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << stack_int.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << stack_int.Size() << endl;
                break;
            case 'b':
                cout << "   Bottom: " << stack_int.Element() << endl;
                break;
            case 'P':
                cin >> input;
                stack_int.Push(input);
                cout << "   Push " << input << endl;
                cout << stack_int;
                break;
            case 'p':
                cout << "   Pop: " << stack_int.Top() << endl;
                stack_int.Pop();
                cout << stack_int;
                break;
            case 'd':
                cout << stack_int;
                break;
            default:
                cout << "\tWarning: Invalid input!\n";
                break;
        }
        cout << "\n>> ";
        cin >> in;
    }

    cout << "\n<Stack Function Demonstration> Type: float\n";
    cout << "Munipulate two stacks by the following instructions:\n";
    cout << " e: exit, \t\ts: object size, \tc: object capacity, \td: display stack, \n b: bottom element, \tP: push input, \t\tp: pop\n";
    cout << "\n>> ";
    cin >> in;
    while (in != 'e') {
        switch (in) {
            case 'c':
                cout << "   Capacity: " << stack_float.Get_capacity() << endl;
                break;
            case 's':
                cout << "   Size: " << stack_float.Size() << endl;
                break;
            case 'b':
                cout << "   Bottom: " << stack_float.Element() << endl;
                break;
            case 'P':
                cin >> inputf;
                stack_float.Push(inputf);
                cout << "   Push " << inputf << endl;
                cout << stack_float;
                break;
            case 'p':
                cout << "   Pop" << stack_float.Top() << endl;
                stack_float.Pop();
                cout << stack_float;
                break;
            case 'd':
                cout << stack_float;
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
#include <iostream>
#include "List.h"

using std::cin;
using std::cout;

int main(void)
{
    List<int> list;

    list.InsertFront(1);
    list.InsertFront(2);
    list.InsertFront(3);
    list.Insert(2, 210);
    cout << "\n>> Insert 1, 2, 3, and then insert 210 as the 2nd element\n" << list;

    list.Delete(3);
    cout << "\n>> Delete the third elements\n" << list;
    cout << "\n>> Show front : " << list.Front() << "\n>>      back  : " << list.Back();
    list.InsertFront(10);
    list.InsertFront(100);
    list.InsertFront(1000);
    cout << '\n' << "\n>> Insert 10, 100, 1000 at front\n" << list;
    cout << "\n>> Get(3) :" << list.Get(3) << '\n';
    list.DeleteBack();
    cout << "\n>> Delete Back:\n" <<list;
    list.DeleteFront();
    cout << "\n>> Delete Front:\n" <<list;

    return 0;
}
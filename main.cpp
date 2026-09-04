#include <iostream>
#include "singlelinkedlist.cpp"

int main()
{
    linked_list<int> ll;
    for(int i = 1; i < 11; ++i)
        ll.push_front(i);
    std::cout << ll << std::endl;
    ll.remove(ll.search(5));
    std::cout << ll << std::endl;
    ll.insert(ll.search(8), 88);
    std::cout << ll << std::endl;
    ll.reverse();
    std::cout << ll << std::endl;
    ll.remove(ll.front());
    return 0;
}

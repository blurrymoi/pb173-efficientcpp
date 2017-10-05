#include "hash.hpp"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
    HashLinked<int, int> h;

    h.insert(6);
    h.insert(4);
    h.insert(-2);
    h.insert(22);
    
    assert(h.num_items == 4);
    h.insert(4);
    assert(h.num_items == 4);

    return 0;
}

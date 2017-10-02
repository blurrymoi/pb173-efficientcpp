#include "queue.h"
#include <iostream>

using namespace std;

int main()
{
    BoundedQueue<int> q(2);
    q.insert(1);
    q.insert(2);
    int t = q.top();
    assert(t == 2);
    assert(q.size() == 2);
    q.remove();
    assert(q.size() == 1);

    
    return 0;
}

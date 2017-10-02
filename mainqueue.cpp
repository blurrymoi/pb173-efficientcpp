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

    SetQueue<int> s(4);
    for (auto i : {1,2,1,3,7}){
        s.insert(i);
    }
    int i = s.top();
    assert(s.size() == 4);
    assert(i == 7);
    s.remove();
    assert(s.size() == 3);
    assert(s.top() == 3);
    s.insert(9);
    s.insert(8);
    s.insert(7);
    assert(s.size() == 4);
    
    return 0;
}

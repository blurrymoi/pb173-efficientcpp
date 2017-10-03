#include "queue.h"
#include <iostream>
#include <time.h>
#include <random>
#include <climits>
#include <tuple>
#include <math.h>

using namespace std;

void unittests()
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
}

void benchmark()
{
    /* insert 10^7 "random" values
       let's concentrate on ints, we are lazy */
    std::default_random_engine gen{static_cast<unsigned long>(time(NULL))};
    std::uniform_int_distribution<> distr(INT_MIN, INT_MAX);

    BoundedQueue<int> q5(5), q10(10), q10k(10000);
    unsigned upper_bound = pow(10,7);
    
    for(auto q : { make_tuple(q5, "q5"), {q10, "q10"}, {q10k, "q10k"} })
    {
        BoundedQueue<int> qu = std::get<0>(q);
        clock_t vecq_beg = clock();

        for(unsigned i = 0; i < upper_bound; ++i)
            qu.insert(distr(gen));
        while(!qu.empty())
            qu.remove();

        clock_t vecq_end = clock();
        cout << std::get<1>(q) << ": " << vecq_end - vecq_beg << endl;
    }

    SetQueue<int> s5(5), s10(10), s10k(10000);

    for(auto s : { make_tuple(s5, "s5"), {s10, "s10"}, {s10k, "s10k"} })
    {
        SetQueue<int> su = std::get<0>(s);
        clock_t setq_beg = clock();

        for(unsigned i = 0; i < upper_bound; ++i)
            su.insert(distr(gen));
        while(!su.empty())
            su.remove();

        clock_t setq_end = clock();
        cout << std::get<1>(s) << ": " << setq_end - setq_beg << endl;
    }
}

int main()
{
    //unittests();
    benchmark();

    return 0;
}

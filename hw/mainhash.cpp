#include "hash.hpp"
#include <iostream>
#include <string>
#include <assert.h>
#include <time.h>
#include <random>
#include <climits>

using namespace std;

int main()
{
    HashLinked<int, int> h;

    h.insert(6);
    //h.printhashy();

    h.insert(4);
    //h.printhashy();

    h.insert(-2);
    h.insert(22);
    
    assert(h.num_items == 4);
    h.insert(4);
    assert(h.num_items == 4);
    //h.printhashy();

    assert( h.find(6)->item == 6 );
    assert( h.find(5) == nullptr );
 
    std::default_random_engine gen{static_cast<unsigned long>(time(NULL))};
    std::uniform_int_distribution<> distr(INT_MIN, INT_MAX);

    HashLinked<int,int> hl;
    clock_t vecq_beg = clock();    

    for( unsigned i = 0; i < 10000000; ++i )
        hl.insert( distr(gen) );
    //while(!qu.empty())
    //    qu.remove();

    clock_t vecq_end = clock();
    cout << "LL: " << vecq_end - vecq_beg << endl;

    return 0;
}

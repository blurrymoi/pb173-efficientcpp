#include "hash.hpp"
#include <iostream>
#include <iomanip>

#include <time.h>
#include <random>
#include <climits>

#include <set>
#include <unordered_set>

using namespace std;

template < typename T >
void benchmark( std::vector< int >& vec )
{
    T t;
    clock_t beg = clock();

    for (auto el : vec)
        t.insert(el);

    for (auto el : vec)
        auto ret = t.find(el);

    clock_t end = clock();
    cout << end - beg << endl;
}

int main()
{

    std::default_random_engine gen{ static_cast< unsigned long >( time(NULL) ) };
    std::uniform_int_distribution<> distr( INT_MIN, INT_MAX );

    std::vector< int > vec;
    for( unsigned i = 0; i < 10000000; ++i ) {  
        vec.push_back( distr(gen) );
    }

    cout << "*10^7, measured in clock() things with -O2*" << endl;

    cout << setw(8) << "set: ";
    benchmark< std::set<int> >(vec);

    cout << setw(8) << "u_set: ";
    benchmark< std::unordered_set<int> >(vec);
    
    cout << setw(8) << "LL: ";
    benchmark< HashLinked<int,int> >(vec);

    cout << setw(8) << "prob: ";
    benchmark< HashProbing<int,int> >(vec);    

    return 0;
}

#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

#include "hash.hpp"
#include <iostream>
#include <iomanip>

#include <random>
#include <climits>
#include <cstdlib>

#include <set>
#include <unordered_set>
#include <brick-benchmark>

// ./hw2 category:hash | gnuplot > out.pdf

#define MAX 300000

using namespace std;
using namespace brick;

struct Hashy : benchmark::Group
{

    std::vector< int > vec;

    Hashy()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "size";
        x.unit = "iter";
        x.min = 512;
        x.step = 2;
        x.max = MAX;
        x.log = true;
        x.normalize = benchmark::Axis::Div;

        y.type = benchmark::Axis::Qualitative;
        y.name = "type";
        
        y.min = 1;
        y.max = 4;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "set";
                case 2: return "u_set";
                case 3: return "hash_ll";
                case 4: return "hash_probe";
            }
        };
    }

    std::string describe() { return "category:hash"; }

    virtual void setup( int _p, int _q )
    {
        std::srand( 0 );
        vec.clear();
        for( size_t i = 0; i < _p; ++i ) {  
            vec.push_back( std::rand() );
        }

        p = _p; q = _q;
    }

    BENCHMARK( insert )
    {
        switch ( q )
        {
            case 1: run< std::set<int> >(); break;
            case 2: run< std::unordered_set<int> >(); break;
            case 3: run< HashLinked<int,int> >(); break;
            case 4: run< HashProbing<int,int> >(); break;
        }
    }

    BENCHMARK( erase )
    {
        switch ( q )
        {
            case 1: er< std::set<int> >(p); break;
            case 2: er< std::unordered_set<int> >(p); break;
            case 3: er< HashLinked<int,int> >(p); break;
            case 4: er< HashProbing<int,int> >(p); break;
        }
    }

    template < typename T >
    void run()
    {
        T t;

        for (auto el : vec)
            t.insert(el);
    }

    template < typename T >
    void er( unsigned p )
    {
        T t;
        int to_erase = vec[0];

        for (unsigned i = 0; i < p; ++i) {
            t.insert(vec[i]);
            if(i % 3 == 0) {
                t.erase(to_erase);
                to_erase = vec[i];
            }
        }
    }
};

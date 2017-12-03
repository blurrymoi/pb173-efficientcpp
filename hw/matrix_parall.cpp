#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

#include "matrix_parall.hpp"
#include <brick-benchmark>
#include <cassert>
#include <type_traits>

// ./hw3 category:matrix | gnuplot > matrix.pdf
// may want to increase ULIMIT

using namespace brick;

#define MAX 1024

struct Matr : benchmark::Group
{
    Matr()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "rows";
        x.unit = "iter";
        x.min = 1;
        x.step = 2;
        x.max = MAX;
        x.log = true;

        y.type = benchmark::Axis::Qualitative;
        y.name = "type";
        
        y.min = 1;
        y.max = 4;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "naive";
                case 2: return "\"cache-efficient\"";
                case 3: return "tiling";
                case 4: return "parallel";
            }
        };
    }

    std::string describe() { return "category:matrix"; }

    #define ONE std::integral_constant< int, 1 >()

    BENCHMARK( multiply )
    {
        switch ( q )
        {
            case 1: run< m >( p, ONE ); break;
            case 2: run< m_c >( p, ONE ); break;
            case 3: run < m_t >( p, ONE ); break;
            case 4: run < m_p >( p, ONE ); break;
        }
    }

    template< template< int > class bench, int i >
    void run( int p, std::integral_constant< int, i > ) {
        if ( i == p )
            bench< i >::run();
        else
            run< bench >( p, std::integral_constant< int, i*2 >() );
    }

    template< template< int > class bench >
    void run( int p, std::integral_constant< int, 2*MAX > ) {
        assert( false );
        return;
    }
};



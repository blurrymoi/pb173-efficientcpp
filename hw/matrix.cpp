#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

#include "matrix.hpp"
#include <iostream>
#include <brick-benchmark>

// ./hw3 category:matrix | gnuplot > matrix.pdf

using namespace std;
using namespace brick;


struct Matr : benchmark::Group
{
    Matr()
    {
        x.type = benchmark::Axis::Quantitative;
        x.name = "rows";
        x.unit = "iter";
        x.min = 1;
        x.step = 2;
        x.max = 1024;
        x.log = true;

        y.type = benchmark::Axis::Qualitative;
        y.name = "type";
        
        y.min = 1;
        y.max = 2;
        y._render = []( int i )
        {
            switch ( i )
            {
                case 1: return "naive";
                case 2: return "cache-optimal";
            }
        };
    }

    std::string describe() { return "category:matrix"; }

    BENCHMARK( multiply )
    {
        switch ( q )
        {
            case 1: multiply(p); break;
            case 2: multiply_cache(p); break;
        }
    }

    //template < int m >
    void multiply( int p )
    {
        switch (p){
            case 1: m<1>(); break;
            case 2: m<2>(); break;
            case 4: m<4>(); break;
            case 8: m<8>(); break;
            case 16: m<16>(); break;
            case 32: m<32>(); break;
            case 64: m<64>(); break;
            case 128: m<128>(); break;
            case 256: m<256>(); break;
            case 512: m<512>(); break;
            case 1024: m<1024>(); break;
            default: break;
        }
        /*
        if (m<i)
            do<2*m>(i);
        else
            really_do<m>();
        */
    }

    void multiply_cache(int p)
    {
        switch (p){
            case 1: mc<1>(); break;
            case 2: mc<2>(); break;
            case 4: mc<4>(); break;
            case 8: mc<8>(); break;
            case 16: mc<16>(); break;
            case 32: mc<32>(); break;
            case 64: mc<64>(); break;
            case 128: mc<128>(); break;
            case 256: mc<256>(); break;
            case 512: mc<512>(); break;
            case 1024: mc<1024>(); break;
            default: break;
        }
    }
};


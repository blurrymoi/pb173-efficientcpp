#pragma once
#include "matrix.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>


bool ended = false;

void loop_fn( std::mutex& mutex, std::queue< std::function< void() > >& jobs ) {
    while(true)
    {
        if(ended) return;

        mutex.lock();
        if (!jobs.empty())
        {
            std::function< void() > job = jobs.front();
            jobs.pop();
            job();
        }
        mutex.unlock();
    }
}


template< size_t rows, size_t r, size_t c, unsigned num_threads=2 >
Matrix< rows, c > mult_parallel( const Matrix< rows, r > &m1, const Matrix< r, c > &m2 )
{
    std::mutex _mutex;
    std::queue< std::function< void() > > _jobs;
    std::vector< std::thread > _threads;

    Matrix< rows, c > ret;

    for(size_t i = 0; i < num_threads; ++i) {
        _threads.push_back( std::thread( loop_fn, std::ref( _mutex ), std::ref( _jobs ) ));
    }

    // riadok, celu, riadok

    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < c; ++j){
	    double sum = 0;
	    for(size_t mid = 0; mid < r; ++mid){
	        sum += m1._data[i][mid]*m2._data[mid][j];
	    }
	    ret._data[i][j] = sum;
        }

    while(true)
    {   
        _mutex.lock();
        if(_jobs.empty()) {
            ended = true;
            _mutex.unlock();
            break;
        }
        _mutex.unlock();
    }
    for(auto& thr : _threads)
        thr.join();
    return ret;
}



template< int p >
struct m_p {
static double run() {
    Matrix< p,p > m1(false), m2(false);
    return mult_parallel(m1, m2)._data[0][0];
}
};

#pragma once
#include "matrix.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>


std::atomic< bool > ended { false };

template< size_t rows, size_t r, size_t c >
using ComputeFuncT = void( const std::array< double, r >&, const Matrix< r, c >&, std::array< double, rows >& );

template< size_t rows, size_t r, size_t c >
void job_fn( const std::array< double, r >& data, const Matrix< r, c >& m2, std::array< double, rows >& ret ) {
    for(size_t j = 0; j < c; ++j){
    double sum = 0;
    for(size_t mid = 0; mid < r; ++mid){
        sum += data[mid]*m2._data[mid][j];
    }
    ret[j] = sum;
    }
}


template< size_t rows, size_t r, size_t c >
void loop_fn( std::mutex& mutex, std::queue< std::function< void() > > &jobs ) {
    while(true)
    {
        if(ended) return;

        if (mutex.try_lock()) {
            //std::cout << "TRYLOCKED" << std::endl;
            if (!jobs.empty())
            {   //std::cout << "*unempty, size " << jobs.size() << std::endl;
                if (jobs.size() == 1) { /*std::cout << "*ENDED*" <<std::endl;*/ ended = true; }  /* fishy */           
                auto job = jobs.front();
                jobs.pop();
                mutex.unlock();
                //std::cout << "**unlocked, performing job" << std::endl;
                job();
            } else { mutex.unlock(); return; }
        }
    }
}


template< size_t rows, size_t r, size_t c, unsigned num_threads=2 >
Matrix< rows, c > mult_parallel( const Matrix< rows, r > &m1, const Matrix< r, c > &m2 )
{
    using namespace std;

    std::mutex _mutex;
    std::queue< std::function< void() > > _jobs;    
    std::vector< std::thread > _threads;

    Matrix< rows, c > ret;

    // riadok, celu, riadok

    for(size_t i = 0; i < rows; ++i) {
            _jobs.push( std::bind( job_fn< rows, r, c >, std::cref(m1._data[i]), std::cref(m2), std::ref(ret._data[i]) ) );
            //cout << "pushed back job i: " << i << endl;
	    
        /*double sum = 0;
	    for(size_t mid = 0; mid < r; ++mid){
	        sum += m1._data[i][mid]*m2._data[mid][j];
	    }
	    ret._data[i][j] = sum;*/
        }
    
    for(size_t i = 0; i < num_threads; ++i) {
        _threads.push_back( std::thread( loop_fn< rows, r, c >, std::ref( _mutex ), std::ref( _jobs ) ));
        //cout << "thread " << i << " created" << endl;
    }

    //cout << "HERE" << endl;

    /*
    while(true)
    {   
        _mutex.lock();
        if(_jobs.empty()) {
            ended = true;
            cout << "ENDED" << endl;
            _mutex.unlock();
            break;
        }
        _mutex.unlock();

        if (ended) break;
    }
    */
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

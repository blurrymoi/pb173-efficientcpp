#pragma once
#include <array>
#include <iostream>
#include <random>
#include <climits>
#include <stdexcept> //invalid_argument

// ULIMIT!!
#define TILE 16

using namespace std; //DELETE

template< size_t rows, size_t cols >
class Matrix {

public:
    Matrix(){
        std::mt19937 rand{ 0 };     //rand{seed}  
        std::uniform_int_distribution< int > dist( 1, 50 );//INT_MAX );
        
        for(size_t i = 0; i < cols; ++i)
            for(size_t j = 0; j < rows; ++j)
                _data[j][i] = dist(rand);
    }

    Matrix(bool){
        for(size_t i = 0; i < cols; ++i)
            for(size_t j = 0; j < rows; ++j)
                _data[j][i] = 0;
    }

    template< size_t r, size_t c >
    Matrix< rows,c > operator*( const Matrix< r,c >& m ) const {
        if (cols != r)
            throw std::invalid_argument("wrong size");
        Matrix< rows, c > ret(false);
        
        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < c; ++j){
                double sum = 0;
                for(size_t mid = 0; mid < cols; ++mid){
                    sum += _data[i][mid]*m._data[mid][j];
                }
                ret._data[i][j] = sum;
            }
        return ret;
    }

    template< size_t r, size_t c >
    Matrix< rows,c > mult_( const Matrix< r,c >& m ) const {
        if (cols != r)
            throw std::invalid_argument("wrong size");
        Matrix< rows, c > ret(false);        

    for(size_t mid = 0; mid < rows; ++mid) {
        for(size_t i = 0; i < cols; ++i)
            for(size_t j = 0; j < c; ++j) {
                //double sum = 0;
                    //cout << "i " << i << " j " << j << " mid " << mid << endl;
                    //cout << "A coords " << mid << " " << i << endl;
                    //cout << "B coords " << i << " " << j << endl;             
                    //cout << "C coords " << mid << " " << j << endl;       
                    ret._data[mid][j] += _data[mid][i] * m._data[i][j];//sum += _data[i][mid]*m._data[mid][j];
                }
                //ret._data[i][j] = sum;
            }
        
        return ret;
    }

//private:
public:
    std::array< std::array< double, cols >, rows > _data;

    template< size_t r, size_t c >
    friend std::ostream& operator<< (std::ostream& o, const Matrix< r,c >& m);
};


template< int p >
void m() {
    Matrix< p,p > m1, m2;
    Matrix< p,p > m3 = m1*m2;
}

template< int p >
void mc() {
    Matrix< p,p > m1, m2;
    Matrix< p,p > m3 = m1.mult_(m2);
}

template< size_t rows, size_t cols >
std::ostream& operator<< (std::ostream& o, const Matrix< rows, cols >& m)  
{
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j)
            o << m._data[i][j] << " ";
        o << "\n";
    }
    o << "\n";
    return o;  
}  

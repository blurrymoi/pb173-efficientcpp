#pragma once
#include <array>
#include <iostream>
#include <random>
#include <climits>
#include <stdexcept> //invalid_argument
#include <algorithm>


#define TILE 16

template< size_t rows, size_t cols >
class Matrix {

public:
    Matrix(bool){
        std::mt19937 rand{ 0 };     //rand{seed}  
        std::uniform_int_distribution< int > dist( 1, 50 );
        
        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < cols; ++j)
                _data[i][j] = dist(rand);
    }

    Matrix(){
        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < cols; ++j)
                _data[i][j] = 0;
    }

    template< size_t r, size_t c >
    Matrix< rows,c > operator*( const Matrix< r,c >& m ) const {
        if (cols != r)
            throw std::invalid_argument("wrong size");
        Matrix< rows, c > ret;
        
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
        Matrix< rows, c > ret;        

    for(size_t mid = 0; mid < rows; ++mid)
        for(size_t i = 0; i < cols; ++i)
            for(size_t j = 0; j < c; ++j)
                ret._data[mid][j] += _data[mid][i] * m._data[i][j];
        
        return ret;
    }

    template< size_t r, size_t c >
    Matrix< rows,c > mult_tile( const Matrix< r,c >& m ) const {

    Matrix< rows,c > ret;

    for ( size_t j = 0; j < rows; j += TILE )
        for ( size_t k = 0; k < cols; k += TILE )
            for ( size_t i = 0; i < c; i += TILE )
                for ( size_t x = j; x < std::min(rows,j+TILE); x++ )
                    for ( size_t z = k; z < std::min(cols,k+TILE); z++ )                    
                        for ( size_t y = i; y < std::min(c,i+TILE); y++ )
                            ret._data[x][y] += _data[x][z] * m._data[z][y];
    return ret;
    }

//almost private:
    std::array< std::array< double, cols >, rows > _data;

    template< size_t r, size_t c >
    friend std::ostream& operator<< (std::ostream& o, const Matrix< r,c >& m);
};

template< int p >
struct m {
static double run() {
    Matrix< p,p > m1(false), m2(false);
    return (m1 * m2)._data[0][0];
}
};

template< int p >
struct m_c {
static double run() {
    Matrix< p,p > m1(false), m2(false);
    return m1.mult_(m2)._data[0][0];
}
};

template< int p >
struct m_t {
static double run() {
    Matrix< p,p > m1(false), m2(false);
    return m1.mult_tile(m2)._data[0][0];
}
};


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

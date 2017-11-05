#pragma once
#include <array>
#include <iostream>
#include <random>
#include <climits>
#include <stdexcept> //invalid_argument

template< size_t rows, size_t cols >
class Matrix {

public:
    Matrix(){
        std::mt19937 rand{ 0 };     //rand{seed}  
        std::uniform_int_distribution< int > dist( 1, 50 );//INT_MAX );
        
        for(size_t i = 0; i < rows; ++i)
            for(size_t j = 0; j < cols; ++j)
                _data[i][j] = dist(rand);
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
                    std::cout << "i,j,mid -- " << i << " " << j << " " << mid << std::endl;
                    std::cout << _data[i][mid] << " * " << m._data[mid][j] << std::endl;
                    sum += _data[i][mid]*m._data[mid][j];
                }
                ret._data[i][j] = sum;
            }
        return ret;
    }

//private:
public:
    std::array< std::array< double, cols >, rows > _data;

    template< size_t r, size_t c >
    friend std::ostream& operator<< (std::ostream& o, const Matrix< r,c >& m);
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

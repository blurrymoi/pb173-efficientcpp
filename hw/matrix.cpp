#include "matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
    Matrix<3,2> m;
    auto n = m;
    auto p(n);
    Matrix<2,4> mm;
    
    cout << m;    
    cout << n;
    cout << p;
    cout << mm;
    cout << m*mm;

    return 0;
}


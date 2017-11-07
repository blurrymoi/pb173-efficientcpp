#include "matrix.hpp"
#include <iostream>
using namespace std;


int main()
{
/*
    Matrix<3,2> m;
    auto n = m;
    auto p(n);
    Matrix<2,4> mm;
    
    cout << m;    
    cout << n;
    cout << p;
    cout << mm;
    cout << m*mm;

    Matrix<1,1> m1, m2;
    Matrix<1,1> m3 = m1*m2;
*/

    Matrix<3,2> m_c;
    cout << m_c;
    Matrix<2,4> m_c2;
    cout << m_c2;
    Matrix<3,4> m_c3 = m_c.mult_(m_c2);
    cout << m_c3;

    return 0;
}



#include "matrix.hpp"
#include <iostream>
#include <cassert>

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
    assert(m3._data[0][0] = m1._data[0][0]*m2._data[0][0]);
    */

    /*
    Matrix<2,4> m(false);
    cout << m;
    //m._data[0][1] = 2;
    //m._data[2][1] = 3;
    //m._data[3][1] = 4;
    for(auto i = 0; i < 4; i++)
        m._data[0][i] = i+1;
    cout << m;
    */


    Matrix<3,2> m_c;
    //m_c._data[0] = std::array<double,3>{28,30,36};
    //m_c._data[1] = {43,31,43};
    m_c._data = {std::array<double,2>({28,43}),{30,31},{36,43}};
    cout << m_c;
    Matrix<2,4> m_c2;
    m_c2._data = {std::array<double,4>({28,36,31,28}),{30,43,43,43}};
    cout << m_c2;
    Matrix<3,4> m_c3 = m_c.mult_(m_c2);
    cout << m_c3;
    assert((m_c3._data == std::array<std::array<double,4>,3>({std::array<double,4>({2074,2857,2717,2633}),{1770,2413,2263,2173},{2298,3145,2965,2857}})));

    Matrix<3,4> c4 = m_c * m_c2;
    assert((c4._data == std::array<std::array<double,4>,3>({std::array<double,4>({2074,2857,2717,2633}),{1770,2413,2263,2173},{2298,3145,2965,2857}})));


    return 0;
}



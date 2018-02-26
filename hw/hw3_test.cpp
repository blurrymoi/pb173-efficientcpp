#include "matrix.hpp"
#include "matrix_parall.hpp"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    std::array<std::array<double,4>,3> res {std::array<double,4>({2074,2857,2717,2633}),{1770,2413,2263,2173},{2298,3145,2965,2857}};

    //Matrix<100,100> m12_1, m12_2;
    //auto result4 = mult_parallel(m12_1, m12_2);

    
    Matrix<3,2> m_c;
    m_c._data = {std::array<double,2>({28,43}),{30,31},{36,43}};
    cout << m_c;
    Matrix<2,4> m_c2;
    m_c2._data = {std::array<double,4>({28,36,31,28}),{30,43,43,43}};
    cout << m_c2;
    Matrix<3,4> m_c3 = m_c.mult_(m_c2);
    cout << m_c3;
    assert((m_c3._data == res));
    
    Matrix<3,4> c4 = m_c * m_c2;
    assert((c4._data == res));

    
    Matrix<3,4> c5 = m_c.mult_tile(m_c2);
    cout << c5;
    assert((c5._data == res));
    
    
    Matrix<500,500> m12_1, m12_2;
    auto result1 = m12_1*m12_2;
    auto result2 = m12_1.mult_(m12_2);
    auto result3 = m12_1.mult_tile(m12_2);
    auto result4 = mult_parallel(m12_1, m12_2);
    
    assert(( result1._data == result2._data ));
    assert(( result1._data == result3._data ));
    assert(( result1._data == result4._data ));

    return 0;
}



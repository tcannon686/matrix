#include <iostream>
#include <cassert>
#include "matrix.hpp"

using namespace tmat;

bool testMultiply()
{
    cout << "test multiply" << endl;

    Matrix<3, 3, float> a{
        { 10, 0, -3 },
        { -2, -4, 1 },
        { 3, 0, 2 }
    };
    Matrix<3, 3, float> b{
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9}
    };
    Matrix<3, 3, float> expected {
        { -11, -4, 3 },
        { -11, -16, -21 },
        { 17, 22, 27 }
    };

    cout << a << " * " << b << endl;
    cout << "Expected: " << expected << endl;
    cout << "Actual: " << a * b << endl;
    
    return expected == a * b;
}

int main(int argc, char *argv[])
{
    assert(testMultiply());
}


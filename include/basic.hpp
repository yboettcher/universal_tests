#include <cmath>
#include <universal/number/posit/posit.hpp> // just any universal type to make sure the namespace exists
#include <iostream>

using namespace sw::universal;
using namespace std;


template <typename ScalarStandard, typename ScalarTest>
bool test_basic() {
    ScalarStandard a = 3.0;
    ScalarStandard b = 7.0;

    // addition
    ScalarStandard c = a + b;
    ScalarStandard d = ScalarStandard(ScalarTest(a) + ScalarTest(b));

    if (abs(c - d) > 0.001) {
        std::cerr << "Addition: a: " << a << "; b: " << b << "; c: " << c << "; d: " << d << std::endl;
        return false;
    }

    // subtraction
    c = a - b;
    d = ScalarStandard(ScalarTest(a) - ScalarTest(b));

    if (abs(c - d) > 0.001) {
        std::cerr << "Subtraction: a: " << a << "; b: " << b << "; c: " << c << "; d: " << d << std::endl;
        return false;
    }

    // multiplication
    c = a * b;
    d = ScalarStandard(ScalarTest(a) * ScalarTest(b));

    if (abs(c - d) > 0.001) {
        std::cerr << "Multiplication: a: " << a << "; b: " << b << "; c: " << c << "; d: " << d << std::endl;
        return false;
    }

    // division. Flipped for a more interesting result for integers
    c = b / a;
    d = ScalarStandard(ScalarTest(b) / ScalarTest(a));

    if (abs(c - d) > 0.001) {
        std::cerr << "Division: a: " << a << "; b: " << b << "; c: " << c << "; d: " << d << std::endl;
        return false;
    }

    // not implemented for all types
    /*
    // sqrt
    c = sqrt(a + b);
    d = ScalarStandard(sqrt(ScalarTest(a) + ScalarTest(b)));

    if (abs(c - d) > 0.0001) {
        return false;
    }

    // log
    c = log(a + b);
    d = ScalarStandard(log(ScalarTest(a) + ScalarTest(b)));

    if (abs(c - d) > 0.0001) {
        return false;
    }
*/

    return true;
}

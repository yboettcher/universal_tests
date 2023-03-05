#include <iostream>
#include <cmath>
#include <complex>
#include <cassert>
#include <Eigen/Dense>

#include "scalar.hpp"
#if defined(TEST_EIGENVALUES) || defined(TEST_EIGENVECTORS)
#include "eigen.hpp"
#endif

#if defined(TEST_SINGULAR_VALUES) || defined(TEST_SINGULAR_VECTORS_U) || defined(TEST_SINGULAR_VECTORS_V)
#include "singular.hpp"
#endif

#ifdef TEST_GMRES
#include "gmres.hpp"
#endif

#ifdef TEST_STD
#include "std.hpp"
#endif

#ifdef TEST_MTL
#include "eigen_mtl.hpp"
#endif

#ifdef TEST_BASIC
#include "basic.hpp"
#endif

int main() {

#ifdef TEST_EIGENVALUES
    bool pass = test_eigenvalues<ScalarStd, Scalar>();
#endif

#ifdef TEST_EIGENVECTORS
    bool pass = test_eigenvectors<ScalarStd, Scalar>();
#endif

#ifdef TEST_SINGULAR_VALUES
    bool pass = test_singular_values<ScalarStd, Scalar>();
#endif

#ifdef TEST_SINGULAR_VECTORS_V
    bool pass = test_singular_vectors_U<ScalarStd, Scalar>();
#endif

#ifdef TEST_SINGULAR_VECTORS_U
    bool pass = test_singular_vectors_V<ScalarStd, Scalar>();
#endif

#ifdef TEST_GMRES
    bool pass = test_gmres<ScalarStd, Scalar>();
#endif

#ifdef TEST_STD
    bool pass = test_std_functions<ScalarStd, Scalar>();
#endif

#ifdef TEST_MTL
    bool pass = test_eigenvalues_mtl<ScalarStd, Scalar>();
#endif

#ifdef TEST_BASIC
    bool pass = test_basic<ScalarStd, Scalar>();
#endif

    assert(pass);
}

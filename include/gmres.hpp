#pragma once
#include "common.hpp"
#include <Eigen/Dense>
#include <unsupported/Eigen/IterativeSolvers>
#include <iostream>

using Eigen::MatrixX;
using Eigen::MatrixXd;
using Eigen::GMRES;
using Eigen::VectorX;
using Eigen::VectorXd;
using Eigen::VectorXcd;

template <typename Scalar_>
VectorXcd run_gmres(MatrixXd mat, VectorXd vec) {
    MatrixX<Scalar_> mat_scalar = cast_matrix<double, Scalar_>(mat);
    VectorX<Scalar_> vec_scalar = cast_matrix<double, Scalar_>(vec);

    GMRES<MatrixX<Scalar_>> solver(mat_scalar);
    VectorX<Scalar_> x = solver.solve(vec_scalar);

    VectorXcd x_double = cast_complex_matrix<Scalar_, double>(x);
    std::cerr << x_double << std::endl;

    return x_double;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_gmres() {
    MatrixXd random_mat = gen_random_matrix(10);
    VectorXd random_vec = gen_random_vector(10);

    VectorXcd standard = run_gmres<ScalarStandard>(random_mat, random_vec);
    VectorXcd test = run_gmres<ScalarTest>(random_mat, random_vec);
    VectorXcd diff = standard - test;

    VectorXcd residual_standard = random_mat * standard - random_vec;
    VectorXcd residual_test = random_mat * test - random_vec;

    std::cerr << residual_standard << std::endl;
    std::cerr << residual_test << std::endl;

    double max_diff = diff.cwiseAbs().maxCoeff();
    std::cerr << max_diff << std::endl;

    return max_diff < 1e-10;
}

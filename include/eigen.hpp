#pragma once
#include "common.hpp"
#include <Eigen/Dense>
#include <algorithm>

using Eigen::VectorXcd;
using Eigen::VectorXd;
using Eigen::VectorX;
using Eigen::MatrixXcd;
using Eigen::MatrixXd;
using Eigen::MatrixX;
using Eigen::ComplexEigenSolver;

template <typename Scalar_>
VectorXcd compute_eigenvalues(MatrixXd mat) {
    MatrixX<Scalar_> mat_scalar = cast_matrix<double, Scalar_>(mat);

    ComplexEigenSolver<MatrixX<Scalar_>> solver(mat_scalar);

    MatrixX<std::complex<Scalar_>> eigs = solver.eigenvalues();

    VectorXcd eigs_double = cast_complex_matrix<Scalar_, double>(eigs);
    std::cerr << "values: " << eigs_double.transpose() << std::endl;

    return eigs_double;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_eigenvalues() {
    Eigen::MatrixXd random_mat = gen_random_matrix(5);// Eigen::MatrixXd::Random(5, 5);

    Eigen::VectorXcd eigs_standard_double = compute_eigenvalues<ScalarStandard>(random_mat);
    Eigen::VectorXcd eigs_test_double = compute_eigenvalues<ScalarTest>(random_mat);

    VectorXd eigs_standard_abs = eigs_standard_double.cwiseAbs();
    VectorXd eigs_test_abs = eigs_test_double.cwiseAbs();

    // sort to avoid differences due to ordering. We loose the actual values, but if their absolutes are exactly the same, it is likely, their complex values were equal too
    std::sort(eigs_standard_abs.data(), eigs_standard_abs.data() + eigs_standard_abs.size());
    std::sort(eigs_test_abs.data(), eigs_test_abs.data() + eigs_test_abs.size());

    Eigen::VectorXd diff = eigs_standard_abs - eigs_test_abs;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}

template <typename Scalar_>
MatrixXcd compute_eigenvectors(MatrixXd mat) {
    MatrixX<Scalar_> mat_scalar = cast_matrix<double, Scalar_>(mat);
    std::cerr << "matrix: " << std::endl << mat_scalar << std::endl;

    ComplexEigenSolver<MatrixX<Scalar_>> solver(mat_scalar);

    MatrixX<std::complex<Scalar_>> eigs = solver.eigenvectors();

    MatrixXcd eigs_double = cast_complex_matrix<Scalar_, double>(eigs);
    std::cerr << "vectors: " << std::endl << eigs_double << std::endl;

    return eigs_double;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_eigenvectors() {
    Eigen::MatrixXd random_mat = gen_random_matrix(5); // Eigen::MatrixXd::Random(5, 5);

    Eigen::MatrixXcd eigs_standard_double = compute_eigenvectors<ScalarStandard>(random_mat);
    Eigen::MatrixXcd eigs_test_double = compute_eigenvectors<ScalarTest>(random_mat);

    MatrixXd eigs_standard_abs = eigs_standard_double.cwiseAbs();
    MatrixXd eigs_test_abs = eigs_test_double.cwiseAbs();

    // sort to avoid differences due to ordering. We loose the actual vectors, but if their absolutes are exactly the same, it is likely, their complex values were equal too
    std::sort(eigs_standard_abs.data(), eigs_standard_abs.data() + eigs_standard_abs.rows() * eigs_standard_abs.cols());
    std::sort(eigs_test_abs.data(), eigs_test_abs.data() + eigs_test_abs.rows() * eigs_test_abs.cols());

    Eigen::MatrixXd diff = eigs_standard_abs - eigs_test_abs;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}

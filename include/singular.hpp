#pragma once
#include "common.hpp"
#include <Eigen/Dense>

template<typename ScalarStandard, typename ScalarTest>
bool test_singular_values() {
    Eigen::MatrixXd random_mat = gen_random_matrix(5);//Eigen::MatrixXd::Random(5, 5);

    Eigen::MatrixX<ScalarStandard> random_mat_standard = cast_matrix<double, ScalarStandard>(random_mat);
    Eigen::MatrixX<ScalarTest> random_mat_test = cast_matrix<double, ScalarTest>(random_mat);


    Eigen::BDCSVD<Eigen::MatrixX<ScalarStandard>> svd_standard(random_mat_standard, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::BDCSVD<Eigen::MatrixX<ScalarTest>> svd_test(random_mat_test, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::MatrixX<std::complex<ScalarStandard>> sv_standard = svd_standard.singularValues();
    Eigen::MatrixX<std::complex<ScalarTest>> sv_test = svd_test.singularValues();

    Eigen::MatrixXcd sv_standard_double = cast_complex_matrix<ScalarStandard, double>(sv_standard);
    Eigen::MatrixXcd sv_test_double = cast_complex_matrix<ScalarTest, double>(sv_test);
    Eigen::MatrixXcd diff = sv_standard_double - sv_test_double;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_singular_vectors_U() {
    Eigen::MatrixXd random_mat = gen_random_matrix(5);//Eigen::MatrixXd::Random(5, 5);

    Eigen::MatrixX<ScalarStandard> random_mat_standard = cast_matrix<double, ScalarStandard>(random_mat);
    Eigen::MatrixX<ScalarTest> random_mat_test = cast_matrix<double, ScalarTest>(random_mat);


    Eigen::BDCSVD<Eigen::MatrixX<ScalarStandard>> svd_standard(random_mat_standard, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::BDCSVD<Eigen::MatrixX<ScalarTest>> svd_test(random_mat_test, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::MatrixX<std::complex<ScalarStandard>> svu_standard = svd_standard.matrixU();
    Eigen::MatrixX<std::complex<ScalarTest>> svu_test = svd_test.matrixU();

    Eigen::MatrixXcd svu_standard_double = cast_complex_matrix<ScalarStandard, double>(svu_standard);
    Eigen::MatrixXcd svu_test_double = cast_complex_matrix<ScalarTest, double>(svu_test);
    Eigen::MatrixXcd diff = svu_standard_double - svu_test_double;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_singular_vectors_V() {
    Eigen::MatrixXd random_mat = gen_random_matrix(5);//Eigen::MatrixXd::Random(5, 5);

    Eigen::MatrixX<ScalarStandard> random_mat_standard = cast_matrix<double, ScalarStandard>(random_mat);
    Eigen::MatrixX<ScalarTest> random_mat_test = cast_matrix<double, ScalarTest>(random_mat);

    Eigen::BDCSVD<Eigen::MatrixX<ScalarStandard>> svd_standard(random_mat_standard, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::BDCSVD<Eigen::MatrixX<ScalarTest>> svd_test(random_mat_test, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::MatrixX<std::complex<ScalarStandard>> svv_standard = svd_standard.matrixV();
    Eigen::MatrixX<std::complex<ScalarTest>> svv_test = svd_test.matrixV();

    Eigen::MatrixXcd svv_standard_double = cast_complex_matrix<ScalarStandard, double>(svv_standard);
    Eigen::MatrixXcd svv_test_double = cast_complex_matrix<ScalarTest, double>(svv_test);
    Eigen::MatrixXcd diff = svv_standard_double - svv_test_double;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}

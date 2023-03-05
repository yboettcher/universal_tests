#pragma once
#include <Eigen/Dense>


Eigen::MatrixXd test_matrix() {
    Eigen::MatrixXd mat(3, 3);
    mat << 1, 2, 3,
           4, 5, 6,
           7, 8, 9;
    return mat;
}

Eigen::VectorXd test_vector() {
    Eigen::VectorXd vec(3);
    vec << 1, 2, 3;
    return vec;
}

// based on an idea here:
// https://math.stackexchange.com/questions/273061/how-to-randomly-construct-a-square-full-ranked-matrix-with-low-determinant
Eigen::MatrixXd gen_random_matrix(int size) {
    Eigen::MatrixXd mat_l = Eigen::MatrixXd::Random(size, size);
    Eigen::MatrixXd mat_u = Eigen::MatrixXd::Random(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col) {
                mat_l.coeffRef(row, col) = 1;
                mat_u.coeffRef(row, col) = 1;
            }
            if (row > col) {
                mat_u.coeffRef(row, col) = 0;
            }
            if (row < col) {
                mat_l.coeffRef(row, col) = 0;
            }
        }
    }

    return mat_l * mat_u;
}

Eigen::MatrixXd gen_random_vector(int size) {
    Eigen::VectorXd vec = Eigen::VectorXd::Random(size);

    return vec;
}

template<typename ScalarIn, typename ScalarOut>
Eigen::MatrixX<ScalarOut> cast_matrix(Eigen::MatrixX<ScalarIn> mat_in) {
    Eigen::MatrixX<ScalarOut> mat_out = Eigen::MatrixX<ScalarOut>::Zero(mat_in.rows(), mat_in.cols());

    for (int r = 0; r<mat_in.rows(); r++) {
        for (int c = 0; c<mat_in.cols(); c++) {
            mat_out.coeffRef(r,c) = ScalarOut(mat_in.coeffRef(r, c));
        }
    }

    return mat_out;
}

template<typename ScalarIn, typename ScalarOut>
Eigen::MatrixX<std::complex<ScalarOut>> cast_complex_matrix(Eigen::MatrixX<std::complex<ScalarIn>> mat_in) {
    Eigen::MatrixX<std::complex<ScalarOut>> mat_out = Eigen::MatrixX<std::complex<ScalarOut>>::Zero(mat_in.rows(), mat_in.cols());

    for (int r = 0; r<mat_in.rows(); r++) {
        for (int c = 0; c<mat_in.cols(); c++) {
            mat_out.coeffRef(r,c) = std::complex(ScalarOut(mat_in.coeffRef(r, c).real()), ScalarOut(mat_in.coeffRef(r, c).imag()));
        }
    }

    return mat_out;
}


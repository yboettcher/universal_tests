#pragma once
#include <algorithm>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/mtl/operation/random.hpp>
#include <cmath>

#pragma once
#include <Eigen/Dense>


mtl::mat::dense2D<double> test_matrix_mtl() {
    mtl::mat::dense2D<double> mat(3, 3);
    mat = 1, 2, 3,
          4, 5, 6,
          7, 8, 9;
    return mat;
}

mtl::mat::dense2D<double> test_vector_mtl() {
    mtl::mat::dense2D<double> vec(3, 1);
    vec = 1, 2, 3;
    return vec;
}

// based on an idea here:
// https://math.stackexchange.com/questions/273061/how-to-randomly-construct-a-square-full-ranked-matrix-with-low-determinant
mtl::mat::dense2D<double> gen_random_matrix_mtl(int size) {
    mtl::mat::dense2D<double> mat_l(size, size);
    mtl::mat::dense2D<double> mat_u(size, size);
    mtl::mat::dense2D<double> mat(size, size);
    random(mat_l);
    random(mat_u);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col) {
                mat_l[row][col] = 1;
                mat_u[row][col] = 1;
            }
            if (row > col) {
                mat_u[row][col] = 0;
            }
            if (row < col) {
                mat_l[row][col] = 0;
            }
        }
    }

    mat = mat_l * mat_u;
    return mat;
}

mtl::mat::dense2D<double> gen_random_vector_mtl(int size) {
    mtl::mat::dense2D<double> vec(size, 1);
    random(vec);

    return vec;
}

template<typename ScalarIn, typename ScalarOut>
mtl::mat::dense2D<ScalarOut> cast_matrix_mtl(mtl::mat::dense2D<ScalarIn> mat_in) {
    mtl::mat::dense2D<ScalarOut> mat_out(mat_in.num_rows(), mat_in.num_cols());

    for (long unsigned int r = 0; r<mat_in.num_rows(); r++) {
        for (long unsigned int c = 0; c<mat_in.num_cols(); c++) {
            mat_out[r][c] = ScalarOut(mat_in[r][c]);
        }
    }

    return mat_out;
}

template<typename ScalarIn, typename ScalarOut>
mtl::mat::dense2D<std::complex<ScalarOut>> cast_complex_matrix_mtl(mtl::mat::dense2D<std::complex<ScalarIn>> mat_in) {
    mtl::mat::dense2D<std::complex<ScalarOut>> mat_out(mat_in.num_rows(), mat_in.num_cols());

    for (long unsigned int r = 0; r<mat_in.rows(); r++) {
        for (long unsigned int c = 0; c<mat_in.cols(); c++) {
            mat_out[r][c] = std::complex(ScalarOut(mat_in[r][c].real()), ScalarOut(mat_in[r][c].imag()));
        }
    }

    return mat_out;
}

mtl::mat::dense2D<double> cWiseAbs(mtl::mat::dense2D<double> mat) {
    mtl::mat::dense2D<double> mat_out(mat.num_rows(), mat.num_cols());
    for (long unsigned int row = 0; row < mat.num_rows(); row++) {
        for (long unsigned int col = 0; col < mat.num_cols(); col++) {
            mat_out[row][col] = std::abs(mat[row][col]);
        }
    }
    return mat_out;
}


mtl::mat::dense2D<double> cWiseAbs(mtl::mat::dense2D<std::complex<double>> mat) {
    mtl::mat::dense2D<double> mat_out(mat.num_rows(), mat.num_cols());
    for (long unsigned int row = 0; row < mat.num_rows(); row++) {
        for (long unsigned int col = 0; col < mat.num_cols(); col++) {
            mat_out[row][col] = std::abs(mat[row][col]);
        }
    }
    return mat_out;
}


mtl::dense_vector<double> cWiseAbs(mtl::dense_vector<double> vec) {
    mtl::dense_vector<double> vec_out(vec.used_memory());
    for (long unsigned int row = 0; row < vec.used_memory(); row++) {
        vec_out[row] = std::abs(vec[row]);
    }
    return vec_out;
}

mtl::dense_vector<double> cWiseAbs(mtl::dense_vector<std::complex<double>> vec) {
    mtl::dense_vector<double> vec_out(vec.used_memory());
    for (long unsigned int row = 0; row < vec.used_memory(); row++) {
        vec_out[row] = std::abs(vec[row]);
    }
    return vec_out;
}

double maxCoeff(mtl::dense_vector<double> vec) {
    double max = vec[0];
    for (long unsigned int row = 0; row < vec.used_memory(); row++) {
        if (vec[row] > max) {
            max = vec[row];
        }
    }
    return max;
}


template <typename Scalar_>
mtl::mat::dense2D<std::complex<double>> compute_eigenvalues_mtl(mtl::mat::dense2D<double> mat) {
    mtl::mat::dense2D<Scalar_> mat_scalar = cast_matrix_mtl<double, Scalar_>(mat);

    mtl::mat::eigenvalue_solver<mtl::mat::dense2D<Scalar_>> solver(mat_scalar);
    solver.setMaxIteration(50);
    solver.calc();

    mtl::mat::dense2D<std::complex<Scalar_>> eigs = solver.get_eigenvalues();

    mtl::mat::dense2D<std::complex<double>> eigs_double = cast_complex_matrix_mtl<Scalar_, double>(eigs);
    std::cerr << "values: " << trans(eigs_double) << std::endl;

    return eigs_double;
}

template<typename ScalarStandard, typename ScalarTest>
bool test_eigenvalues_mtl() {
    mtl::mat::dense2D<double> random_mat(5, 5);// mtl::mat::dense2D<double>::Random(5, 5);
    random(random_mat);

    mtl::mat::dense2D<std::complex<double>> eigs_standard_double = compute_eigenvalues_mtl<ScalarStandard>(random_mat);
    mtl::mat::dense2D<std::complex<double>> eigs_test_double = compute_eigenvalues_mtl<ScalarTest>(random_mat);

    mtl::mat::dense2D<double> eigs_standard_abs;
    eigs_standard_abs = cWiseAbs(eigs_standard_double);
    mtl::mat::dense2D<double> eigs_test_abs;
    eigs_test_abs = cWiseAbs(eigs_test_double);

    mtl::dense_vector<double> eigs_standard_vec(eigs_standard_abs.num_rows());
    mtl::dense_vector<double> eigs_test_vec(eigs_standard_abs.num_rows());

    for (int i = 0; i < eigs_standard_abs.num_rows(); i++) {
        eigs_standard_vec[i] = eigs_standard_abs[i];
        eigs_test_vec[i] = eigs_test_abs[i];
    }

    // sort to avoid differences due to ordering. We loose the actual complex values, but if their absolutes are exactly the same, it is likely, their complex values were equal too
    std::sort(eigs_standard_vec.begin(), eigs_standard_vec.end());
    std::sort(eigs_test_vec.begin(), eigs_test_vec.end());

    mtl::dense_vector<double> diff(eigs_standard_vec.used_memory());
    diff = eigs_standard_vec - eigs_test_vec;

    double max_diff = maxCoeff(cWiseAbs(diff));

    return max_diff < 1e-10;
}

/*
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
    mtl::mat::dense2D<double> random_mat = gen_random_matrix(5); // mtl::mat::dense2D<double>::Random(5, 5);

    Eigen::MatrixXcd eigs_standard_double = compute_eigenvectors<ScalarStandard>(random_mat);
    Eigen::MatrixXcd eigs_test_double = compute_eigenvectors<ScalarTest>(random_mat);

    MatrixXd eigs_standard_abs = eigs_standard_double.cwiseAbs();
    MatrixXd eigs_test_abs = eigs_test_double.cwiseAbs();

    // sort to avoid differences due to ordering. We loose the actual vectors, but if their absolutes are exactly the same, it is likely, their complex values were equal too
    std::sort(eigs_standard_abs.data(), eigs_standard_abs.data() + eigs_standard_abs.rows() * eigs_standard_abs.cols());
    std::sort(eigs_test_abs.data(), eigs_test_abs.data() + eigs_test_abs.rows() * eigs_test_abs.cols());

    mtl::mat::dense2D<double> diff = eigs_standard_abs - eigs_test_abs;

    double max_diff = diff.cwiseAbs().maxCoeff();

    return max_diff < 1e-10;
}*/

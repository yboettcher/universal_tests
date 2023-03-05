#pragma once
#include <cmath>

template <typename ScalarStandard, typename ScalarTest>
bool test_std_functions() {
    double initial = 1507.299792458;

    ScalarStandard standard = ScalarStandard(initial);
    ScalarTest test = ScalarTest(initial);

    // sqrt
    double sqrt_diff = double(std::sqrt(standard)) - double(std::sqrt(test));
    bool sqrt_pass = sqrt_diff < 1e-10;

    // tan
    double tan_diff = double(std::tan(standard)) - double(std::tan(test));
    bool tan_pass = tan_diff < 1e-10;

    // log
    double log_diff = double(std::log(standard)) - double(std::log(test));
    bool log_pass = log_diff < 1e-10;

    // atan
    double atan_diff = double(std::atan(standard)) - double(std::atan(test));
    bool atan_pass = atan_diff < 1e-10;

    // room for more




    return sqrt_pass && tan_pass && log_pass && atan_pass;
}

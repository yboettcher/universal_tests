#include <cmath>
#include <universal/number/posit/posit.hpp>

using Scalar = sw::universal::posit<64,2>;

int main() {

  Scalar a = 1507.2; // arbitrary number
  Scalar b = std::sqrt(a); // arbitrary function from cmath
  return 0;
}
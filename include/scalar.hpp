#pragma once

#ifdef TEST_POSIT
#include <universal/number/posit/posit.hpp>
using Scalar = sw::universal::posit<64, 4>;
using ScalarStd = long double;
#endif

#ifdef TEST_EPOSIT
#include <universal/number/eposit/eposit.hpp>
using Scalar = sw::universal::eposit;
using ScalarStd = long double;
#endif

#ifdef TEST_FIXPNT
#include <universal/number/fixpnt/fixpnt.hpp>
using Scalar = sw::universal::fixpnt<1024, 512>;
using ScalarStd = long double;
#endif

#ifdef TEST_AREAL
#include <universal/number/areal/areal.hpp>
using Scalar = sw::universal::areal<64, 13>;
using ScalarStd = long double;
#endif

#ifdef TEST_CFLOAT
#include <universal/number/cfloat/cfloat.hpp>
using Scalar = sw::universal::cfloat<64, 13>;
using ScalarStd = long double;
#endif

#ifdef TEST_EFLOAT
#include <universal/number/efloat/efloat.hpp>
using Scalar = sw::universal::efloat;
using ScalarStd = long double;
#endif

#ifdef TEST_VALID
#include <universal/number/valid/valid.hpp>
using Scalar = sw::universal::valid<64, 4>;
using ScalarStd = long double;
#endif

#ifdef TEST_UNUM
#include <universal/number/unum/unum.hpp>
using Scalar = sw::universal::unum<64, 4>;
using ScalarStd = long double;
#endif

#ifdef TEST_UNUM2
#include <universal/number/unum2/unum2_impl.hpp>
using Scalar = sw::universal::unum2<64, 4>;
using ScalarStd = long double;
#endif

#ifdef TEST_LNS
#include <universal/number/lns/lns.hpp>
using Scalar = sw::universal::lns<64, 13>;
using ScalarStd = long double;
#endif

#ifdef TEST_LNS2B
#include <universal/number/lns2b/lns2b.hpp>
using Scalar = sw::universal::lns2b<64, 13>;
using ScalarStd = long double;
#endif

#ifdef TEST_SORN
#include <universal/number/sorn/sorn.hpp>
using Scalar = sw::universal::sorn<0, 4, 8>;
using ScalarStd = long double;
#endif

#ifdef TEST_DECIMAL
#include <universal/number/decimal/decimal.hpp>
using Scalar = sw::universal::decimal;
using ScalarStd = long;
#endif

#ifdef TEST_RATIONAL
#include <universal/number/rational/rational.hpp>
using Scalar = sw::universal::rational;
using ScalarStd = long double;
#endif

#ifdef TEST_EINTEGER
#include <universal/number/einteger/einteger.hpp>
using Scalar = sw::universal::einteger<uint32_t>;
using ScalarStd = long;
#endif

#ifdef TEST_INTEGER
#include <universal/number/integer/integer.hpp>
using Scalar = sw::universal::integer<64>;
using ScalarStd = long;
#endif



#ifdef TEST_FLOAT
#include <universal/number/float/float.hpp>
using Scalar = sw::universal::float<64, 2>;
#endif

#ifdef TEST_QUIRE
#include <universal/number/quire/quire.hpp>
using Scalar = sw::universal::quire<64, 2>;
#endif



#ifdef TEST_ADAPTIVEINT
#include <universal/number/adaptiveint/adaptiveint.hpp>
using Scalar = sw::universal::adaptiveint<64, 2>;
#endif

#ifdef TEST_ADAPTIVEFLOAT
#include <universal/number/adaptivefloat/adaptivefloat.hpp>
using Scalar = sw::universal::adaptivefloat<64, 2>;
#endif

#ifdef TEST_ADAPTIVEPOSIT
#include <universal/number/adaptiveposit/adaptiveposit.hpp>
using Scalar = sw::universal::adaptiveposit<64, 2>;
#endif
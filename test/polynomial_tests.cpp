#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "dbhp/polynomial.h"

using namespace std;

namespace dbhp {

  TEST_CASE("Make empty integer polynomial") {
    vector<monomial<int>> ms{};

    polynomial<int> p(ms);

    polynomial<int> q(ms);

    REQUIRE(p == q);
  }

  
}

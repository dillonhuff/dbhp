#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "dbhp/polynomial.h"
#include "dbhp/division.h"

using namespace std;

namespace dbhp {

  TEST_CASE("Make empty integer polynomial") {
    vector<monomial<int>> ms{};

    polynomial<int> p(ms);

    polynomial<int> q(ms);

    REQUIRE(p == q);
  }

  TEST_CASE("Compare different polynomials") {
    vector<monomial<unsigned>> ms{};
    polynomial<unsigned> q(ms);

    vector<unsigned> powers{3, 3};

    monomial<unsigned> m1(5, powers);
    vector<monomial<unsigned>> ms1{m1};
    polynomial<unsigned> p(ms1);

    REQUIRE(p != q);
  }

  TEST_CASE("Add int polynomials") {
    vector<unsigned> powers1{1, 3, 2, 0};
    vector<unsigned> powers2{1, 5, 6, 1};

    monomial<int> m1(5, powers1);
    monomial<int> m2(-3, powers2);
    vector<monomial<int>> ms1{m1, m2};
    vector<monomial<int>> ms2{m1};

    vector<monomial<int>> s{2*m1, m2};
    polynomial<int> sum(s);
    
    polynomial<int> p(ms1);
    polynomial<int> q(ms2);
    
    REQUIRE(sum == p + q);
  }

  TEST_CASE("Polynomial division, 4 / 2 == 2") {
    vector<unsigned> pows1{};
    monomial<int> m1{4, pows1};
    vector<monomial<int>> ms1{m1};
    polynomial<int> p{ms1};
    
    vector<unsigned> pows2{};
    monomial<int> m2{2, pows2};
    vector<monomial<int>> ms2{m2};
    polynomial<int> q{ms2};

    monomial<int> m3{2, pows2};
    vector<monomial<int>> ms3{m3};
    polynomial<int> quot{ms3};

    vector<monomial<int>> z{};
    polynomial<int> rem{z};
    
    division_result<int> res = divide(p, q);

    REQUIRE(res.succeeded());
    REQUIRE(res.q() == quot);
    REQUIRE(res.r() == rem);
  }
}

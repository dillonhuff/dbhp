#pragma once

#include <vector>

namespace dbhp {

  template<typename T>
  class monomial {};

  template<typename T>
  class polynomial {
  public:
    polynomial(const std::vector<monomial<T>>& ) {}
  };

  template<typename T>
  bool operator==(const polynomial<T>&, const polynomial<T>&) {
    return true;
  }
}

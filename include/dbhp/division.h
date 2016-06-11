#pragma once

#include "dbhp/polynomial.h"

namespace dbhp {

  template<typename T>
  class division_result {
  protected:
    bool success;
    polynomial<T> q_res;
    polynomial<T> r_res;
    
  public:
    division_result(const polynomial<T>& q, const polynomial<T>& r)
      : success(true), q_res(q), r_res(r) {}

    bool succeeded() const { return success; }
    polynomial<T> q() const { return q_res; }
    polynomial<T> r() const { return r_res; }
  };

  template<typename T>
  division_result<T> divide(const polynomial<T>& p, const polynomial<T>& q) {
    // assert(p.num_vars() == q.num_vars());
    
    // return rdivide(p, q, zero(p.num_vars));
    return division_result<T>(p, q);
  }

}

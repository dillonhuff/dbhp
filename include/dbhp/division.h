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
    division_result() :
      success(false), q_res(zero<T>()), r_res(zero<T>()) {}

    division_result(const polynomial<T>& q, const polynomial<T>& r)
      : success(true), q_res(q), r_res(r) {}

    bool succeeded() const { return success; }
    polynomial<T> q() const { return q_res; }
    polynomial<T> r() const { return r_res; }
  };

  template<typename T>
  division_result<T> divide(const polynomial<T>& p, const polynomial<T>& q) {
    assert(p.num_vars() == q.num_vars());
    polynomial<T> z = zero<T>();
    return rdivide(p, q, z);
  }

  template<typename T>
  std::pair<bool, unsigned> next_var(const polynomial<T>& f) {
    if (f.num_vars() == 0) {
      return std::pair<bool, unsigned>(false, 0);
    } else {
      return std::pair<bool, unsigned>(true, f.num_vars() - 1);
    }
  }

  template<typename T>
  division_result<T> constant_div(const polynomial<T>& f,
				  const polynomial<T>& g) {
    unsigned nv = f.num_vars();
    T fc = f.constant_value();
    T gc = g.constant_value();
    if (fc % gc == 0) {
      T q = fc / gc;
      return division_result<T>(constant(q, nv), zero<T>());
    }
    return division_result<T>();
  }

  template<typename T>
  division_result<T> rdivide(const polynomial<T>& f,
			     const polynomial<T>& g,
			     const polynomial<T>& q) {

    std::pair<bool, unsigned> nvar = next_var(f);

    if (nvar.first == false) {
      return constant_div(f, g);
    }

    unsigned var = nvar.second;
    polynomial<T> f_lcof = f.lcof(var);
    polynomial<T> g_lcof = g.lcof(var);

    division_result<T> res = divide(f_lcof, g_lcof);
    if (res.succeeded()) {
      
    } else {
      
    }
    assert(false);
  }
  
}

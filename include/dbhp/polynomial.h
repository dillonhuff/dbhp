#pragma once

#include <iostream>
#include <vector>

namespace dbhp {

  template<typename T>
  class monomial {
  protected:
    T coeff;
    std::vector<unsigned> pows;
    
  public:
    monomial(const T p_coeff, const std::vector<unsigned>& p_pows) :
      coeff(p_coeff), pows(p_pows) {}

    monomial<T> scalar_times(const T c) const {
      return monomial<T>(c*coeff, pows);
    }
  };

  template<typename T>
  class polynomial {
  protected:
    std::vector<monomial<T>> monomials;

  public:
    polynomial(const std::vector<monomial<T>>& p_monomials) :
      monomials(p_monomials) {}

    polynomial<T> times(const polynomial<T>& other) const {
      unsigned this_ind = 0;
      unsigned this_size = monomials.size();

      unsigned other_ind = 0;
      unsigned other_size = other.monomials.size();

      std::vector<monomial<T>> new_monos;

      while (this_ind < this_size && other_ind < other_size) {
	this_ind++;
	other_ind++;
      }

      return polynomial<T>(new_monos);
    }

    bool equals(const polynomial<T>& other) const {
      return true;
    }
  };

  template<typename T>
  monomial<T> operator*(const T c, const monomial<T>& m) {
    return m.scalar_times(c);
  }

  template<typename T>
  polynomial<T> operator+(const polynomial<T>& p, const polynomial<T>& q) {
    return p.times(q);
  }

  template<typename T>
  bool operator==(const polynomial<T>& p, const polynomial<T>& q) {
    return p.equals(q);
  }

  template<typename T>
  bool operator!=(const polynomial<T>& p, const polynomial<T>& q) {
    return !(p == q);
  }

  // template<typename T>
  // std::ostream operator<<(std::ostream&, const polynomial<T>&) {
  //   assert(false);
  // }

}

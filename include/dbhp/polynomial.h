#pragma once

#include <iostream>
#include <vector>

namespace dbhp {

  enum order {LESS, EQUAL, GREATER};

  template<typename T>
  class monomial {
  protected:
    T cf;
    std::vector<unsigned> pows;
    
  public:
    monomial(const T p_coeff, const std::vector<unsigned>& p_pows) :
      cf(p_coeff), pows(p_pows) {}

    unsigned num_vars() const { return pows.size(); }

    monomial<T> scalar_times(const T c) const {
      return monomial<T>(c*cf, pows);
    }

    monomial<T> add_coeff(const T c) const {
      return monomial<T>(c + cf, pows);
    }

    T coeff() const { return cf; }
    
    order compare_multidegree(const monomial<T>& other) const {
      assert(other.pows.size() == pows.size());
      for (unsigned i = 0; i < pows.size(); i++) {
	if (pows[i] < other.pows[i]) {
	  return LESS;
	} else if (pows[i] > other.pows[i]) {
	  return GREATER;
	}
      }
      return EQUAL;
    }

    void print(std::ostream& out) const {
      out << cf;
      for (unsigned i = 0; i < pows.size(); i++) {
	//monomials[i].print(out);
	if (i < pows.size() - 1) {
	  out << "*";
	}
      }
    }
  };

  template<typename T>
  class polynomial {
  protected:
    std::vector<monomial<T>> monomials;

  public:
    polynomial(const std::vector<monomial<T>>& p_monomials) :
      monomials(p_monomials) {}

    unsigned num_vars() const { return monomials.back().num_vars(); }

    polynomial<T> plus(const polynomial<T>& other) const {
      unsigned this_ind = 0;
      unsigned this_size = monomials.size();

      unsigned other_ind = 0;
      unsigned other_size = other.monomials.size();

      std::vector<monomial<T>> new_monos;

      while (this_ind < this_size && other_ind < other_size) {

	auto this_m = monomials[this_ind];
	auto other_m = other.monomials[other_ind];
	
	switch (this_m.compare_multidegree(other_m)) {
	case EQUAL:
	  new_monos.push_back(this_m.add_coeff(other_m.coeff()));
	  
	  this_ind++;
	  other_ind++;

	  break;
	case LESS:
	  new_monos.push_back(this_m);

	  this_ind++;

	  break;
	case GREATER:
	  new_monos.push_back(other_m);

	  other_ind++;

	  break;
	default:
	  assert(false);
	}
      }

      while (this_ind < this_size) {
	new_monos.push_back(monomials[this_ind]);
	this_ind++;
      }

      while (other_ind < other_size) {
	new_monos.push_back(monomials[other_ind]);
	other_ind++;
      }
      
      return polynomial<T>(new_monos);
    }

    unsigned num_monomials() const { return monomials.size(); }

    bool equals(const polynomial<T>& other) const {
      return num_monomials() == other.num_monomials();
    }

    polynomial<T> lcof(unsigned var) const {
      assert(false);
    }

    void print(std::ostream& out) const {
      if (num_monomials() == 0) {
	out << "0";
      }
      for (unsigned i = 0; i < num_monomials(); i++) {
	monomials[i].print(out);
	if (i < num_monomials() - 1) {
	  out << " + ";
	}
      }
    }
  };

  template<typename T>
  monomial<T> operator*(const T c, const monomial<T>& m) {
    return m.scalar_times(c);
  }

  template<typename T>
  polynomial<T> operator+(const polynomial<T>& p, const polynomial<T>& q) {
    return p.plus(q);
  }

  template<typename T>
  bool operator==(const polynomial<T>& p, const polynomial<T>& q) {
    return p.equals(q);
  }

  template<typename T>
  bool operator!=(const polynomial<T>& p, const polynomial<T>& q) {
    return !(p == q);
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& out, const polynomial<T>& p) {
    p.print(out);
    return out;
  }

  template<typename T>
  polynomial<T> zero() {
    std::vector<monomial<T>> zm{};
    polynomial<T> z{zm};
    return z;
  }

}

//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef __IR_HPP
#define __IR_HPP
#include "Stencil.hpp"
#include "Grid.hpp"

template <int I>
size_t ir(const Stencil<I>& A, Grid& x, const Grid& b, size_t max_iter, double tol) {
  for (size_t iter = 0; iter < max_iter; ++iter) {
    Grid   r   = b - A * x;
    double rho = dot(r, r);
    std::cout << "||r|| = " << std::sqrt(rho) << std::endl;
    if (std::sqrt(rho) < tol) return iter;
    x += r;
  }
  return max_iter;
}

#endif // __IR_HPP

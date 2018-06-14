//
// This file is part of the course materials for AMATH483/583 at the University
// of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0
// International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Grid.hpp"
#include "Stencil.hpp"

template <>
Grid operator*(const Stencil<5>& A, const Grid& x) {
  Grid y(x);

  for (size_t i = 1; i < x.numX() - 1; ++i) {
    for (size_t j = 1; j < x.numY() - 1; ++j) {
      y(i, j) = x(i, j) - (x(i - 1, j) + x(i + 1, j) + x(i, j - 1) + x(i, j + 1)) / 4.0;
    }
  }
  return y;
}

template <>
Grid operator*(const Stencil<9>& A, const Grid& x) {
  Grid y(x);
  /* 9 point stencil implementation goes here */
  for (size_t i = 1; i < x.numX() - 1; ++i) {
    for (size_t j = 1; j < x.numY() - 1; ++j) {
      y(i, j) = (
        4*( x(i - 1, j) + x(i + 1, j) +x(i, j - 1) +x(i, j + 1) ) + 
        (x(i-1, j-1) + x(i+1,j-1)+ x(i-1, j+1) + x(i+1, j+1))
        )/20.0;
    }
  }

  return y;
}

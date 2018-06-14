//
// This file is part of the course materials for AMATH483/583 at the University
// of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0
// International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Grid.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

Grid operator-(const Grid& X, const Grid& Y) {
  Grid Z(X);
  for (size_t i = 0; i < Z.numX(); ++i) {
    for (size_t j = 0; j < Z.numY(); ++j) {
      Z(i, j) = X(i, j) - Y(i, j);
    }
  }
  return Z;
}

Grid operator+(const Grid& X, const Grid& Y) {
  Grid Z(X);
  for (size_t i = 0; i < Z.numX(); ++i) {
    for (size_t j = 0; j < Z.numY(); ++j) {
      Z(i, j) = X(i, j) + Y(i, j);
    }
  }
  return Z;
}

void operator+=(Grid& Z, const Grid& X) {
  for (size_t i = 0; i < Z.numX(); ++i) {
    for (size_t j = 0; j < Z.numY(); ++j) {
      Z(i, j) += X(i, j);
    }
  }
}

void operator-=(Grid& Z, const Grid& X) {
  for (size_t i = 0; i < Z.numX(); ++i) {
    for (size_t j = 0; j < Z.numY(); ++j) {
      Z(i, j) -= X(i, j);
    }
  }
}

Grid operator*(double a, const Grid& Y) {
  Grid Z(Y);
  for (size_t i = 1; i < Z.numX() - 1; ++i) {
    for (size_t j = 1; j < Z.numY() - 1; ++j) {
      Z(i, j) = a * Y(i, j);
    }
  }
  return Z;
}

double dot(const Grid& X, const Grid& Y) {
  double sum = 0.0;
  for (size_t i = 0; i < X.numX(); ++i) {
    for (size_t j = 0; j < X.numY(); ++j) {
      sum += X(i, j) * Y(i, j);
    }
  }
  return sum;
}


void swap(Grid& x, Grid& y) { x.swap(y); }

size_t jacobi(Grid& X0, Grid& X1, size_t max_iters, double tol) {
  assert(X0.numX() == X1.numX() && X0.numY() == X1.numY());

  for (size_t iter = 0; iter < max_iters; ++iter) {
    double rnorm = 0.0;
    for (size_t i = 1; i < X0.numX() - 1; ++i) {
      for (size_t j = 1; j < X0.numY() - 1; ++j) {
        X1(i, j) = (X0(i - 1, j) + X0(i + 1, j) + X0(i, j - 1) + X0(i, j + 1)) / 4.0;
        rnorm += (X1(i, j) - X0(i, j)) * (X1(i, j) - X0(i, j));
      }
    }
    rnorm = std::sqrt(rnorm);
    std::cout << "||X0-X1|| = " << rnorm << std::endl;
    if (rnorm < tol) return 0;
    swap(X0, X1);
  }
  return -1;
}

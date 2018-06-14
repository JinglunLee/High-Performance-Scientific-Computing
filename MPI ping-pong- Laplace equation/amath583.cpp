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
#include "amath583.hpp"
#include "Vector.hpp"
#include <random>
#include <functional>

double dot(const Vector& x, const Vector& y) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i) * y(i);
  }
  return sum;
}

double twoNorm(const Vector& x) {
  return sqrt(dot(x, x));
}

void randomize(Vector& x) {
  static std::default_random_engine             generator;
  static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  static auto                                   dice = std::bind(distribution, generator);

  for (int i = 0; i < x.num_rows(); ++i) {
    x(i) = dice();
  }
}


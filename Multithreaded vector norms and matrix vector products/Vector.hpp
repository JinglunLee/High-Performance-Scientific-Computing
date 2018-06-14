//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2017
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
// 

#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <vector>
#include <cstddef>

class Vector {
public:
  Vector(size_t M) : num_rows_(M), storage_(num_rows_) {}

        double& operator()(size_t i)       { return storage_[i]; }
  const double& operator()(size_t i) const { return storage_[i]; }

  size_t num_rows() const { return num_rows_; }
  const auto begin() const { return storage_.begin(); }
  auto begin() {return storage_.begin(); }
  const auto end() const {return storage_.end(); }
  auto end() {return storage_.end(); }

private:
  size_t num_rows_;
  std::vector<double> storage_;  
};

#endif // VECTOR_HPP

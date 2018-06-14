//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "Vector.hpp"
#include "amath583.hpp"
#include <cmath>
#include <iostream>
#include <mpi.h>
#include <string>

double mpiTwoNorm(const Vector& local_x) {
  double rho = dot(local_x, local_x), sigma = 0;
  MPI::COMM_WORLD.Reduce(&rho, &sigma, 1, MPI::DOUBLE, MPI::SUM, 0);
  return std::sqrt(sigma);
}

int main(int argc, char* argv[]) {
  MPI::Init();

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  unsigned long size = 1024;

  if (0 == myrank) {
    if (argc >= 2) size = std::stol(argv[1]);
  }
  MPI::COMM_WORLD.Bcast(&size, 1, MPI::UNSIGNED_LONG_LONG, 0);

  Vector x(size);
  randomize(x);

  double sigma = mpiTwoNorm(x);

  double seq  = twoNorm(x);
  double Pseq = sqrt(mysize * (seq * seq));
  if (0 == myrank) std::cout << "#\tseq\tPseq\tmpi\tdiff" << std::endl;
  std::cout << myrank << "\t" << seq << "\t" << Pseq << "\t" << sigma << "\t" << std::abs(sigma - Pseq) << std::endl;

  MPI::Finalize();

  return 0;
}

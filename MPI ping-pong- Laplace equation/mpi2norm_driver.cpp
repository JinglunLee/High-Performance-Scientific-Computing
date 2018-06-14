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
  /* write me */
  MPI::COMM_WORLD.Allreduce(&rho, &sigma, 1, MPI::DOUBLE, MPI::SUM);
  return std::sqrt(sigma);
}


int main(int argc, char* argv[]) {
  MPI::Init();

  size_t myrank = MPI::COMM_WORLD.Get_rank();
  size_t mysize = MPI::COMM_WORLD.Get_size();

  unsigned long size = 1024;
  
  /* write me */
    if (argc >= 2) size = std::stol(argv[1]);

  Vector x(size*mysize);

  if (0 == myrank) {
    randomize(x);
  }
    //MPI::COMM_WORLD.Bcast(&size, 1, MPI::UNSIGNED_LONG_LONG, 0);
  
  Vector local_x(size);
  MPI::COMM_WORLD.Scatter(&x(0), size, MPI::DOUBLE, &local_x(0), size, MPI::DOUBLE, 0);

  double sigma = mpiTwoNorm(local_x);
  Vector sigma_arr(mysize);
  MPI::COMM_WORLD.Gather(&sigma, 1, MPI::DOUBLE, &sigma_arr(0), 1, MPI::DOUBLE, 0);
  double seq =0;
  if (0 == myrank){
    
    seq = twoNorm(x);                    // two norm of the local vector

    std::cout << "#\tseq\tmpi\tdiff" << std::endl;
    for (size_t i=0; i < mysize; ++i){
    std::cout << myrank << "\t" << seq << "\t" << sigma_arr(i) << "\t" << std::abs(sigma_arr(i) - seq) << std::endl;
    myrank++;
    }
  }
  
  MPI::Finalize();

  return 0;
}

#include "Vector.hpp"
#include "amath583.hpp"
#include <cmath>
#include <iostream>
#include <mpi.h>
#include <string>


int main(int argc, char* argv[]) {
  MPI::Init();

 // int token     = 0;
  size_t rounds = 1;
  if (argc >= 2) rounds = std::stol(argv[1]);

  int myrank = MPI::COMM_WORLD.Get_rank();
  //int mysize = MPI::COMM_WORLD.Get_size();
  Vector lx(1024);
  randomize(lx);
  double rho = twoNorm(lx);

  std::cout << myrank << ": " << std::sqrt(rho) << std::endl;

  MPI::Finalize();
  return 0;
}
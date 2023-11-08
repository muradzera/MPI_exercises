#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  // Initialisation
  MPI_Init(&argc, &argv);
  // Reading size and rank
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Printing
  std::cout << "Hello world, from process #" << rank <<std::endl;

  // Finalisation
  MPI_Finalize();
  return 0;
}

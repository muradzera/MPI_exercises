#include <mpi.h>

// You have access to the following global variables :
int world_rank, world_size;
MPI_Comm custom_comm1, custom_comm2, custom_comm3, tmp;

// The tmp communicator is provided if you need to point somewhere, where you don't
// care about the outputted communicator. For instance, when using MPI_UNDEFINED as color.

// world_rank : rank of the process on MPI_COMM_WORLD
// world_size : size of MPI_COMM_WORLD
// These two variables are already initialized when splitting() is called

void splitting() {
  int color;
  MPI_Comm *new_comm;

  // 1- First splitting here.
  // With only one call to MPI_Comm_split, you should be able to split processes 0-3 in custom_comm1
  // and processes 4-6 in custom_comm2
  color = (world_rank < 4) ? 0 : 1;
  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm1);

  // 2- Second splitting here
  // Now put processes 0 and 4 in custom_comm3
  color = (world_rank % 4 == 0) ? 0 : MPI_UNDEFINED;
  MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &tmp);

  if (color == 0) {
    new_comm = &custom_comm3;
  } else {
    new_comm = &tmp;
  }

  // Broadcast to make sure everything is correct
  MPI_Bcast(&color, 1, MPI_INT, 0, *new_comm);
}

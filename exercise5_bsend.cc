
#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int number;

  char buffer[sizeof(int) + MPI_BSEND_OVERHEAD];

  if (rank == 0) {
    MPI_Buffer_attach(buffer, sizeof(buffer));
  }

  for (int i = 0; i < 3; i++) {
    if (rank == 0) {
      number = i * 10;

      MPI_Bsend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

      std::cout << "Process 0 sent " << number << "\n";

    } else if (rank == 1) {
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      std::cout << "Process 1 received " << number << "\n";
    }
  }

  if (rank == 0) {
    void *old_buffer;
    int old_size;
    MPI_Buffer_detach(&old_buffer, &old_size);
  }

  MPI_Finalize();
  return 0;
}

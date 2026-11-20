
#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int number;
  MPI_Status status;

  for (int i = 0; i < 3; i++) {
    if (rank == 0) {
      number = i * 10;

      MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

      std::cout << "Process 0 sent " << number << "\n";

    } else if (rank == 1) {
      MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

      std::cout << "Process 1 received " << number << " from process "
                << status.MPI_SOURCE << "\n";
    }
  }

  MPI_Finalize();
  return 0;
}

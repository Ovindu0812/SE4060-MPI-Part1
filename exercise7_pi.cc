
#include <cstdlib>
#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const long long N = 10000000;
  long long samples = N / size;

  if (rank < N % size)
    samples++;

  unsigned int seed = 12345 + rank * 10007;
  long long local_inside = 0;

  MPI_Barrier(MPI_COMM_WORLD);
  double start = MPI_Wtime();

  for (long long i = 0; i < samples; i++) {
    double x = (double)rand_r(&seed) / RAND_MAX;
    double y = (double)rand_r(&seed) / RAND_MAX;

    if (x * x + y * y <= 1.0)
      local_inside++;
  }

  if (rank == 0) {
    long long total_inside = local_inside;

    for (int i = 1; i < size; i++) {
      long long received;
      MPI_Status status;

      MPI_Recv(&received, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
               &status);

      total_inside += received;
    }

    double pi = 4.0 * total_inside / N;
    double end = MPI_Wtime();

    std::cout << "Pi = " << pi << "\n";
    std::cout << "Execution Time = " << end - start << " seconds\n";

  } else {
    char buffer[sizeof(long long) + MPI_BSEND_OVERHEAD];

    MPI_Buffer_attach(buffer, sizeof(buffer));

    MPI_Bsend(&local_inside, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);

    void *old_buffer;
    int old_size;

    MPI_Buffer_detach(&old_buffer, &old_size);
  }

  MPI_Finalize();
  return 0;
}

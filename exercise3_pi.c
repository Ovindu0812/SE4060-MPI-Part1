
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int rank, size;
  long long n = 10000000;
  long long local_inside = 0;
  long long total_inside = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long long samples = n / size;

  if (rank < n % size) {
    samples++;
  }

  unsigned int seed = 12345 + rank * 10007;

  MPI_Barrier(MPI_COMM_WORLD);
  double start = MPI_Wtime();

  for (long long i = 0; i < samples; i++) {
    double x = (double)rand_r(&seed) / RAND_MAX;
    double y = (double)rand_r(&seed) / RAND_MAX;

    if (x * x + y * y <= 1.0) {
      local_inside++;
    }
  }

  MPI_Reduce(&local_inside, &total_inside, 1, MPI_LONG_LONG, MPI_SUM, 0,
             MPI_COMM_WORLD);

  double end = MPI_Wtime();

  if (rank == 0) {
    double pi = 4.0 * total_inside / n;
    printf("Pi = %.8f\n", pi);
    printf("Execution Time = %.9f seconds\n", end - start);
  }

  MPI_Finalize();
  return 0;
}

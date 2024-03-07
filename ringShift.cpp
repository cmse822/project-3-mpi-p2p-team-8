#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtasks, rank;
    int idx;
    int length = 1;
    char *sendbuf = (char *)malloc(length * sizeof(char));
    char *recvbuf = (char *)malloc(length * sizeof(char));
    double start_time = 0;
    double end_time = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (idx = 0; idx < numtasks; idx++) {
        if (rank == idx) {
            start_time = MPI_Wtime();
            printf("Rank %d sending to %d\n", rank, (rank + 1) % numtasks);
            MPI_Sendrecv(sendbuf, length, MPI_CHAR, (rank + 1) % numtasks, 0, sendbuf, length, MPI_CHAR, (rank - 1 + numtasks) % numtasks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            end_time = MPI_Wtime();
        }
    }

    double total_time = end_time - start_time;
    printf("Time to complete one roundabout %d: %f\n", length, total_time);
    MPI_Finalize();

    return 0;
}
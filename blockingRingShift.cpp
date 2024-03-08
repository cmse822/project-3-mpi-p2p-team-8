#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtasks, rank;
    int step_idx;
    int length = 1;
    char *sendbuf = (char *)malloc(length * sizeof(char));
    char *recvbuf = (char *)malloc(length * sizeof(char));
    double start_time = 0;
    double end_time = 0;
    int token = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        token = 1;
    }

    for (step_idx = 0; step_idx < numtasks; step_idx++)
    {
        if (step_idx != rank)
        {
            
        }
        int next_rank = (rank + 1) % numtasks;
        int prev_rank = (rank - 1 + numtasks) % numtasks;

        int recv_token;

        start_time = MPI_Wtime();
        MPI_Sendrecv(&token, 1, MPI_INT, next_rank, 0, &recv_token, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        end_time = MPI_Wtime();

        printf("Rank %d received token %d from rank %d\n", rank, recv_token, prev_rank);
        printf("Rank %d sending token %d to rank %d\n", rank, recv_token, next_rank);
        printf("\n");
    }

    double total_time = end_time - start_time;
    printf("Time to complete the ring %d: %f\n", length, total_time);
    MPI_Finalize();

    return 0;
}
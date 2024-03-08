#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtasks, rank;
    int step_idx;
    int length = 1;
    char *sendbuf = (char *)malloc(length * sizeof(char));
    char *recvbuf = (char *)malloc(length * sizeof(char));
    int next_rank;
    int prev_rank;
    int message_size[6] = {2, 4, 8, 16, 32, 64};
    int total_message_size = 0;
    int total_message_size_matrix[6] = {};
    int num_iterations = 5;

    double start_time = 0;
    double end_time = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int send_token = rank;
    int recv_token;

    next_rank = (rank + 1) % numtasks;
    prev_rank = (rank + numtasks - 1) % numtasks;


    MPI_Barrier(MPI_COMM_WORLD);


    for (int i = 0; i < (sizeof(message_size) / sizeof(int)); i++)
    {
        start_time = MPI_Wtime();
        char *buffer = (char *)malloc(message_size[i] * sizeof(char));
        total_message_size = 0;
        for (int n = 0; n < num_iterations; n++)
        {
            MPI_Sendrecv(&send_token, 1, MPI_INT, next_rank, 0, &recv_token, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("Rank %d received token %d from rank %d\n", rank, recv_token, prev_rank);
            // printf("Rank %d sending token %d to rank %d\n", rank, send_token, next_rank);
            // printf("\n");
        }

        total_message_size_matrix[i] = total_message_size;

        end_time = MPI_Wtime();
        double total_time = end_time - start_time;
        printf("Finalized for data size %d:  %f\n", message_size[i], total_time);
    }

    // printf("Rank %d received token %d from rank %d\n", rank, recv_token, prev_rank);
    // printf("Rank %d sending token %d to rank %d\n", rank, send_token, next_rank);
    // printf("\n");

    MPI_Finalize();

    return 0;
}
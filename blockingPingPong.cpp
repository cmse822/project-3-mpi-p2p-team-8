#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    // Found on page 100 of Parallel Programming for Science and Engineering Textbook.
    int numtasks, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int processA,processB;
     processA = 0; processB = 1;


    if (rank==0) {
        printf("Ping-pong between ranks %d--%d\n",
           processA,processB);
    }
    


    double send_data = 1.;
    int message_size = 2;
    int num_iterations = 100;
    char *buffer = (char *)malloc(message_size * sizeof(char));

    // let process A be rank = 0
    // let process B be rank = 1
    double start_time = 0;
    double end_time = 0;

    
    int message_size [12] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int total_message_size = 0;
    int total_message_size_matrix [12] = {};

    for (i = 0; i < length(message_size); i++) {
        total_message_size = 0;
        for (int n=0; n<num_iterations; n++) {
            if (rank == 0) {
                start_time = MPI_Wtime();

                MPI_Send(buffer,message_size,MPI_CHAR, processB,0,MPI_COMM_WORLD);
                MPI_Recv(buffer,message_size,MPI_CHAR, processB,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                total_message_size += message_size

                end_time = MPI_Wtime();
            } else if (rank == 1){
                start_time = MPI_Wtime();
                MPI_Recv(buffer,message_size,MPI_CHAR, processA,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Send(buffer,message_size,MPI_CHAR,processA,0,MPI_COMM_WORLD);
                
                total_message_size += message_size
                end_time = MPI_Wtime();
            }

        }

        total_message_size_matrix[i] = total_message_size;
    }

    
    double total_time = end_time - start_time;
    printf("Time to complete the ping-pong exchange with message size %d: %f\n", length, total_time);
    MPI_Finalize();
    return 0;
}
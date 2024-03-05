#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    // Found on page 100 of Parallel Programming for Science and Engineering Textbook.
    int numtasks, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int processA,processB;
     processA = 0; processB = numtasks-1;


    if (procno==0) {
        printf("Ping-pong between ranks %d--%d\n",
           processA,processB);
    }
    

    double *buffer;
    double send_data = 1.;
    int length = 1;
    int num_iterations = 1;

    // let process A be rank = 0
    // let process B be rank = 1

    for (int n=0; n<num_iterations; n++) {
        if (rank == 0) {
            double start_time = MPI_Wtime();

            MPI_Send (buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD)
            MPI_Recv(buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE)

            double end_time = MPI_Wtime();
        } else {
            double start_time = MPI_Wtime();
            MPI_Recv(buffer,length,MPI_DOUBLE,
                processA,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE)
            MPI_Send(buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD)
            double end_time = MPI_Wtime();
        }

    }
    
    double total_time = end_time - start_time;
    printf("Time to complete the ping-pong exchange with message size %d: %d", length, total_time);
    MPI_Finalize();
    return 0;
}
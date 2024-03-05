#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    // Found on page 100 of Parallel Programming for Science and Engineering Textbook.
    int numtasks, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
<<<<<<< Updated upstream
    int processA,processB;
     processA = 0; processB = 1;


    if (rank==0) {
        printf("Ping-pong between ranks %d--%d\n",
           processA,processB);
    }
    

    char *buffer;
    double send_data = 1.;
    int length = 1;
    int num_iterations = 1;

    // let process A be rank = 0
    // let process B be rank = 1
    double start_time = 0;
    double end_time = 0;

    for (int n=0; n<num_iterations; n++) {
        if (rank == 0) {
            start_time = MPI_Wtime();

            MPI_Send(buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD);
            MPI_Recv(buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

            end_time = MPI_Wtime();
        } else {
            start_time = MPI_Wtime();
            MPI_Recv(buffer,length,MPI_DOUBLE,
                processA,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Send(buffer,length,MPI_DOUBLE,
            processB,0,MPI_COMM_WORLD);
            end_time = MPI_Wtime();
        }

    }
    
    double total_time = end_time - start_time;
    printf("Time to complete the ping-pong exchange with message size %d: %d", length, total_time);
=======
    double send_data = 1.;
    // TODO: init start_node
    // TODO: init end_node (We should know where the end node is)
    // for node in nodes
        // TODO: Halt the start_node+1
        // TODO: Pass the data to start_node+1
        // TODO: update the start_node
    if ( /*I am process A*/) {
    // TODO: 
        MPI_Send (/*to process B*/ )
        MPI_Recv(/*from process B*/)
    } else {
        MPI_Recv(/*from process A*/)
        MPI_Send(/*to process A*/)
    }

    /*
    start_node = 0
    num_nodes = 2 // to N

    for (int i = 0; i < num_nodes-1; i++) {
        if (rank == start_node) {

            MPI_Send(&send_data, 1, MPI_DOUBLE, start_node+1, 0, MPI_COMM_WORLD);

            MPI_Recv(&send_data, 1, MPI_DOUBLE, start_node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        } else if (rank == num_nodes-1) {
            MPI_Send(&send_data, 1, MPI_DOUBLE, start_node, 0, MPI_COMM_WORLD);
            MPI_Recv(&send_data, 1, MPI_DOUBLE, start_node+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        start_node++;
    }

// TODO: In the time/byte graph, moment the curve starts to change is the moment we hit the bandwidth limit.
    */

>>>>>>> Stashed changes
    MPI_Finalize();
    return 0;
}
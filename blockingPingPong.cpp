#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int numtasks, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    double send_data = 1.;
    if ( /*I am process A*/) {
        MPI_Send (/*to process B*/ )
        MPI_Recv(/*from process B*/)
    } else {
        MPI_Recv(/*from process A*/)
        MPI_Send(/*to process A*/)
    }

    MPI_Finalize();
    return 0;
}
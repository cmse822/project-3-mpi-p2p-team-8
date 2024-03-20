#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int numtasks, rank;
    int message_size[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int num_iterations = 100;
    int num_sizes = sizeof(message_size) / sizeof(message_size[0]);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(processor_name);

    double *avg_times = (double *)malloc(num_sizes * sizeof(double));
    double *all_avg_times = NULL;
    char(*all_processor_names)[MPI_MAX_PROCESSOR_NAME] = NULL;

    if (rank == 0)
    {
        all_avg_times = (double *)malloc(numtasks * num_sizes * sizeof(double));
        all_processor_names = (char(*)[MPI_MAX_PROCESSOR_NAME])malloc(numtasks * MPI_MAX_PROCESSOR_NAME * sizeof(char));
    }

    for (int i = 0; i < num_sizes; i++)
    {
        char *buffer = (char *)malloc(message_size[i] * sizeof(char));
        double start_time = MPI_Wtime();

        for (int n = 0; n < num_iterations; n++)
        {
            MPI_Sendrecv_replace(buffer, message_size[i], MPI_BYTE, (rank + 1) % numtasks, 0,
                                 (rank + numtasks - 1) % numtasks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        double end_time = MPI_Wtime();
        free(buffer);

        avg_times[i] = (end_time - start_time) / num_iterations;
    }

    MPI_Gather(avg_times, num_sizes, MPI_DOUBLE, all_avg_times, num_sizes, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Gather processor names to identify off and on nodes.
    MPI_Gather(processor_name, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, all_processor_names, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        /*
        * Write the data to a CSV file according to the number of tasks. 
        */
        char filename[256];
        sprintf(filename, "comm_data_%d.csv", numtasks);
        FILE *file = fopen(filename, "w");

        fprintf(file, "Rank,Node,MessageSize,AverageTimePerExchange\n");

        for (int i = 0; i < numtasks; i++)
        {
            for (int j = 0; j < num_sizes; j++)
            {
                fprintf(file, "%d,%s,%d,%f\n", i, all_processor_names[i], message_size[j], all_avg_times[i * num_sizes + j]);
            }
        }

        fclose(file);
    }

    free(avg_times);
    if (rank == 0)
    {
        free(all_avg_times);
        free(all_processor_names);
    }

    MPI_Finalize();
    return 0;
}

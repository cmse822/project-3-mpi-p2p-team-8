#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtasks, rank;
    int next_rank, prev_rank;
    int message_size[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int num_iterations = 100;
    int num_sizes = sizeof(message_size) / sizeof(message_size[0]);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);

    next_rank = (rank + 1) % numtasks;
    prev_rank = (rank + numtasks - 1) % numtasks;

    MPI_Barrier(MPI_COMM_WORLD);

    // Data arrays for gathering results
    double *all_times = NULL;
    double *avg_times = (double *)malloc(num_sizes * sizeof(double));
    char (*all_names)[MPI_MAX_PROCESSOR_NAME] = NULL;

    if (rank == 0) {
        all_times = (double *)malloc(num_sizes * numtasks * sizeof(double));
        all_names = (char (*)[MPI_MAX_PROCESSOR_NAME])malloc(numtasks * MPI_MAX_PROCESSOR_NAME * sizeof(char));
    }

    for (int i = 0; i < num_sizes; i++) {
        double start_time = MPI_Wtime();

        char *buffer = (char *)malloc(message_size[i] * sizeof(char));

        for (int n = 0; n < num_iterations; n++) {
            MPI_Sendrecv(buffer, message_size[i], MPI_BYTE, next_rank, 0,
                         buffer, message_size[i], MPI_BYTE, prev_rank, 0,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        free(buffer);

        double end_time = MPI_Wtime();
        double total_time = end_time - start_time;
        avg_times[i] = total_time / num_iterations;
    }

    // Gather all average times to the root process
    MPI_Gather(avg_times, num_sizes, MPI_DOUBLE, all_times, num_sizes, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Gather all processor names to the root process
    MPI_Gather(processor_name, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, all_names, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Root process writes the data to a single CSV file
    if (rank == 0) {
        FILE *fp = fopen("comm_data.csv", "w");
        fprintf(fp, "NodeName,MessageSize,AverageTimePerExchange\n");

        for (int i = 0; i < numtasks; i++) {
            for (int j = 0; j < num_sizes; j++) {
                fprintf(fp, "%s,%d,%f\n", all_names[i], message_size[j], all_times[i * num_sizes + j]);
            }
        }

        fclose(fp);
    }

    free(avg_times);
    if (rank == 0) {
        free(all_times);
        free(all_names);
    }

    MPI_Finalize();
    return 0;
}

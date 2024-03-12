#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

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
    int num_iterations = 100;
    double start_time = 0;
    double end_time = 0;
    int message_list_length = 12;

    
    
    int message_size [message_list_length] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    int avg_time_matrix [message_list_length] = {};

    for (int i = 0; i < message_list_length; i++) {
        char *buffer = (char *)malloc(message_size[i] * sizeof(char));
        double total_time = 0;

        for (int n=0; n<num_iterations; n++) {
            if (rank == 0) {
                start_time = MPI_Wtime();

                MPI_Send(buffer,message_size[i] / sizeof(char),MPI_CHAR, processB,0,MPI_COMM_WORLD);
                MPI_Recv(buffer,message_size[i] / sizeof(char),MPI_CHAR, processB,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);


                end_time = MPI_Wtime();

            } else if (rank == 1){
                MPI_Recv(buffer,message_size[i] / sizeof(char),MPI_CHAR, processA,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Send(buffer,message_size[i] / sizeof(char),MPI_CHAR,processA,0,MPI_COMM_WORLD);
                
            }

            total_time += end_time - start_time;
        }

        double avg_time = total_time / num_iterations;


        if (rank == 0) {
            printf("Average time to complete the ping-pong exchange with message size %d: %f\n", message_size[i], avg_time);
            printf("avg time: %f:", avg_time, "\n");
            avg_time_matrix[i] = avg_time;
        }
        
    }

    // Specify the name of the new CSV file
    std::string csvFileName = "blockingPingPong.csv";

    // Open a new CSV file for writing
    std::ofstream csvFile(csvFileName);

    // Check if the file is opened successfully
    if (!csvFile.is_open()) {
        std::cerr << "Error opening the file " << csvFileName << std::endl;
        return 1;
    }

    // Write data from the array to the new CSV file
    for (int i = 0; i < message_list_length; ++i) {
        csvFile << avg_time_matrix[i] << ",";
    }

    // Close the CSV file
    csvFile.close();

    
    MPI_Finalize();
    return 0;
}
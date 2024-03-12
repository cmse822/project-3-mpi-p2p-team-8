import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def main():
    csv_file_path_same_architecture = 'nonblockingPingPongSAMEARCHITECTURE.csv'

    csv_file_path_different_architecture = 'nonblockingPingPongDIFFERENTARCHITECTURE.csv'


    # to print specified csv file, change this path!
    csv_file_path_for_graphic = csv_file_path_same_architecture




    message_sizes = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    
    df = pd.read_csv(csv_file_path_for_graphic, low_memory=False)

    # Does not include the unnamed columns element
    avg_time_row_string = df.columns[0:12]

    avg_time_row = [float(value) for value in avg_time_row_string]

    print(avg_time_row)

    plt.figure(figsize = (10,5))
    plt.loglog(message_sizes, avg_time_row, label='Avgerate time per message size', linestyle='-', linewidth=1, color='blue', marker='o')
    #plt.scatter(message_sizes, avg_time_row, label='Avgerate time per message size', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Message size (bytes)')
    plt.ylabel('Average time (seconds)')
 

    plt.legend(loc='upper left',)
    plt.grid(True)

    if csv_file_path_for_graphic == csv_file_path_different_architecture:
        plt.title("Different Architecture Non-BlockingPingPong: Average time per message size")
        plt.savefig("nonblockingPingPongAverageTimePerMessageSizeDIFFERENTARCHITECTURE.png")
    elif csv_file_path_for_graphic == csv_file_path_same_architecture:
        plt.title("Same Architecture Non-BlockingPingPong: Average time per message size")
        plt.savefig("nonblockingPingPongAverageTimePerMessageSizeSAMEARCHITECTURE.png")

    plt.show()


main()
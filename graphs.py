import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def main():
    csv_file_path = 'blockingPingPong.csv'

    message_sizes = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    
    df = pd.read_csv(csv_file_path, low_memory=False)

    # Does not include the unnamed columns element
    avg_time_row = df.columns[0:12]

    plt.figure(figsize = (12,6))
    plt.plot(message_sizes, avg_time_row, label='Avgerate time per message size', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Message size (bytes)')
    plt.ylabel('Average time (seconds)')
    plt.legend(loc='upper left',)
    plt.grid(True)
    plt.title("BlockingPingPong: Average time per message size")
    plt.savefig("blockingPingPongAverageTimePerMessageSizeSAMEARCHITECTURE.png")
    plt.show()

main()
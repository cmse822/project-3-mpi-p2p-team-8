import pandas as pd
import matplotlib.pyplot as plt


def main():
    csv_file_path = 'blockingPingPong.csv'

    message_sizes = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    
    df = pd.read_csv(csv_file_path, low_memory=False)

    print(df)

    avg_time_row = df.iloc[0].tolist()

    
    plt.plot(message_sizes, avg_time_row, label='Avgerate time per message size', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Message size (bytes)')
    plt.ylabel('Average time (seconds)')
    plt.legend(loc='upper left',)
    plt.grid(True)

    plt.title("Average time per message size")
    plt.savefig("blockingPingPongAverageTimePerMessageSize.png")

main()
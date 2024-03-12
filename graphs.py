def main():
    csv_file_path = 'blockingPingPong.csv'

    message_sizes = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    
    df = pd.read_csv(csv_file_path, low_memory=False)

    fig, ax1 = plt.subplots()

    avg_time_row = df.iloc[0].tolist()
    ax1.scatter(message_sizes, avg_time_row, label='Avgerate time per message size', linestyle='-', linewidth=1, color='blue')
    ax1.set_xlabel('Message size (bytes)')
    ax1.set_ylabel('Average time (seconds)')
    ax1.set
    ax1.legend(loc='upper left',)
    ax1.grid(True)

    plt.title("Average time per message size")
    plt.savefig("blockingPingPongAverageTimePerMessageSize.png")

main()
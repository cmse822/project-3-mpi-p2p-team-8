def main():
    csv_name = 'blockingPingPong.csv'
    data = read_csv(csv_name)

    message_sizes = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    
import pandas as pd
import matplotlib.pyplot as plt

file_path = r'C:\Users\jimmy\Desktop\MSU\C_Codes\project-3-mpi-p2p-team-8\comm_data_10_blocking.csv'
data = pd.read_csv(file_path)

data_r = data.groupby('Rank')

plt.figure(figsize=(10, 6))

for name, group in data_r:
    plt.loglog(group['MessageSize'], group['AverageTimePerExchange'], marker='o', label=f'Rank {name}')

plt.title('Average Time Per Exchange vs. Message Size')
plt.xlabel('Message Size')
plt.ylabel('Average Time Per Exchange')
plt.xscale('log')
plt.yscale('log')
plt.legend(title='Rank')
plt.show()

plt.savefig('BlockingRingShift.png')

file_path = r'C:\Users\jimmy\Desktop\MSU\C_Codes\project-3-mpi-p2p-team-8\comm_data_10_nonblocking.csv'
data = pd.read_csv(file_path)

data_r = data.groupby('Rank')

plt.figure(figsize=(10, 6))

for name, group in data_r:
    plt.loglog(group['MessageSize'], group['AverageTimePerExchange'], marker='o', label=f'Rank {name}')

plt.title('Average Time Per Exchange vs. Message Size')
plt.xlabel('Message Size')
plt.ylabel('Average Time Per Exchange')
plt.xscale('log')
plt.yscale('log')
plt.legend(title='Rank')
plt.show()

plt.savefig('NonblockingRingShift.png')

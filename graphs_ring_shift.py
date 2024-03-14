import pandas as pd
import matplotlib.pyplot as plt

file_path = r'comm_data_64_blocking.csv'
data = pd.read_csv(file_path)

data_r = data.groupby('Rank')

plt.figure(figsize=(10, 6))

# Create a dictionary to track which nodes have been added to the plot
added_nodes = {}

for name, group in data_r:
    node = group.Node.values[0]
    label = ''
    if (name > 32 and name < 63):
        color = 'b'
        if (f'Out Node' not in added_nodes):
            label = f'Out Node'
            added_nodes[label] = True
    elif (name < 31 and name > 0):
        color = 'r'
        if (f'In Node' not in added_nodes):
            label = f'In Node'
            added_nodes[label] = True
    else:
        print(1)
        color = 'g'
        if (f'Transition Nodes' not in added_nodes):
            label = f'Transition Nodes'
            added_nodes[label] = True
    
    # Only add the label if the node has not been added to the plot yet
    plt.loglog(group['MessageSize'], group['AverageTimePerExchange'], c=color, marker='o', label=label)

plt.title('Average Time Per Exchange vs. Message Size')
plt.xlabel('Message Size')
plt.ylabel('Average Time Per Exchange')
plt.xscale('log')
plt.yscale('log')
plt.legend(title='Node')
plt.show()

plt.savefig('BlockingRingShift.png')

file_path = r'comm_data_64_nonblocking.csv'
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

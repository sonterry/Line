import networkx as nx

# Define the graph with nodes and distances
graph = {
    '1001': {'1002': 1},
    '1002': {'1001': 1, '1003': 1, '2004': 1},
    '1003': {'1002': 1, '1004': 1, '2003': 1},
    '1004': {'1003': 1, '2002': 1},
    '2001': {'2002': 1},
    '2002': {'2001': 1, '2003': 1, '1004': 1},
    '2003': {'2002': 1, '2004': 1, '1003': 1},
    '2004': {'1002': 1, '2003': 1}
}



# Create a directed graph from the graph dictionary
G = nx.DiGraph(graph)

# Function to write the path to a file
def write_path_to_file(path, filename="path.txt"):
    with open(filename, "w") as file:
        file.write(path)
    return f"Path written to {filename}"

# Function to read the path from a file
def read_path_from_file(filename="path.txt"):
    with open(filename, "r") as file:
        path = file.read()
    return path

# Updated dijkstra_block function to work with networkx and handle blocked nodes
def dijkstra_block(graph, start, goal, blocked):
    blocked_nodes = set(blocked.split('/'))

    # Create a copy of the graph to modify
    G_blocked = graph.copy()

    # Remove blocked nodes
    G_blocked.remove_nodes_from(blocked_nodes)

    try:
        # Find the shortest path
        path = nx.shortest_path(G_blocked, source=start, target=goal, weight='weight')
        return ' -> '.join(path)
    except nx.NetworkXNoPath:
        return "Path not reachable"

# Example usage with corrected function
shortest_path_str = dijkstra_block(G, '1001', '2001', '2003')

# Write and read the path to/from "path.txt"
write_path_to_file(shortest_path_str)
print(read_path_from_file())

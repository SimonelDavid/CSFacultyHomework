import os 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt 
import warnings 

from networkx.algorithms import community

warnings.simplefilter('ignore')

# plot a network -> de la profa
def plotNetwork(G, communities):

    pos = nx.spring_layout(G)  # compute graph layout
    plt.figure(figsize=(4, 4))  # image is 8 x 8 inches 
    nx.draw_networkx_nodes(G, pos, node_size=600, cmap=plt.cm.RdYlBu, node_color = list(communities.values()))
    nx.draw_networkx_edges(G, pos, alpha=0.3)
    nx.draw_networkx_labels(G, pos)
    plt.show()

def greedyCommunitiesDetectionByTool(Graph, no_of_components_to_split=2):
    communities = dict.fromkeys(Graph.nodes, 0)

    conex_components = nx.algorithms.components.number_connected_components(Graph)

    while(no_of_components_to_split > conex_components and conex_components < Graph.number_of_nodes()):
        # Calculam valoarea de centralitate
        centrality = nx.algorithms.centrality.edge_betweenness_centrality(Graph)
        # sortam dupa centralitati
        sorted_edges = sorted(centrality.items(), key = lambda item:item[1], reverse = True)[0]
        # stergem muchia cu cea mai mare centralitate
        Graph.remove_edge(*sorted_edges[0])
        conex_components = nx.algorithms.components.number_connected_components(Graph)

    index = 1
    for community in [c for c in sorted(nx.connected_components(Graph), key=len, reverse=True)]:
        for node in community:
            communities[node] = index
        index += 1

    return communities

if __name__ == "__main__":
    current_directory =  os.getcwd()
    file_path = os.path.join(current_directory,  '/Users/simoneldavid/Documents/CSFacultyHomework/Fourth_semester/Inteligenta Artificiala/Lab2/real/dolphins', 'dolphins.gml')
    Graph = nx.read_gml(file_path, label='id')
    copy_of_graph = Graph.copy()

    plotNetwork(copy_of_graph, greedyCommunitiesDetectionByTool(Graph))
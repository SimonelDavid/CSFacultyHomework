import networkx as nx
import numpy as np

def greedy_modularity_communities(G):
    # initializare
    c = list(nx.connected_components(G)) # fiecare nod este într-o comunitate separată
    Q = calculate_modularity(G, c) # calculează modularitya inițială
    improved = True
    
    while improved:
        improved = False
        for i in range(len(c)):
            for j in range(i+1, len(c)):
                new_c = merge_communities(c[i], c[j]) # unește cele două comunități
                new_Q = calculate_modularity(G, new_c) # calculează modularitya noii comunități
                
                if new_Q > Q:
                    c = new_c
                    Q = new_Q
                    improved = True
    
    return c
    
def calculate_modularity(G, communities):
    m = G.number_of_edges()
    A = nx.to_numpy_array(G)
    Q = 0
    for c in communities:
        c = list(c)
        Ac = A[np.ix_(c, c)]
        kc = np.sum(Ac, axis=1)
        lc = np.sum(kc)
        ec = np.sum(Ac)
        Q += ec/m - lc**2/(4*m**2)
    return Q
    
def merge_communities(c1, c2):
    return [c1.union(c2)] + [c for c in c if c != c1 and c != c2]

# Exemplu de utilizare
edges = [(1,2),(1,3),(1,4),(1,5),(2,6),(2,7),(2,8),(3,9),(4,11),(4,12),(4,13),(5,15),(5,16),(5,17),(6,18),(7,20),(7,21),(8,23),(9,24),(9,25),(11,26),(11,27),(11,28),(13,29),(13,30),(13,31),(18,32),(18,33),(20,34),(20,35),(20,36),(20,37)]
G = nx.Graph(edges)
communities = greedy_modularity_communities(G)
print(f"Numărul de comunități identificate: {len(communities)}")
for i, c in enumerate(communities):
    print(f"Comunitatea {i+1}: {c}")
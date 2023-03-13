import numpy as np
import networkx as nx

def get_community_assign(G, partitions):
    """
    Asignează fiecărui nod din graf o comunitate din lista dată.
    
    :param G: graful dat
    :param partitions: lista de seturi de noduri, fiecare set reprezentând o comunitate
    :return: dicționar ce asociază fiecărui nod o comunitate din lista dată
    """
    node2community = {}
    for i, partition in enumerate(partitions):
        for node in partition:
            node2community[node] = i
    return node2community

def greedy_community_detection(G, max_iter=100):
    """
    Detectează comunitățile din graf folosind algoritmul Greedy.
    
    :param G: graful dat
    :param max_iter: numărul maxim de iterații pentru algoritm
    :return: lista de seturi de noduri, fiecare set reprezentând o comunitate
    """
    # Initializează fiecare nod în propria comunitate
    partitions = [{node} for node in G.nodes()]
    
    for _ in range(max_iter):
        improvement = False
        
        # Parcurge fiecare pereche de noduri
        for node1 in G.nodes():
            for node2 in G.nodes():
                if node1 == node2:
                    continue
                
                # Verifică dacă cele două noduri sunt în aceeași comunitate
                node1_community = None
                node2_community = None
                for i, partition in enumerate(partitions):
                    if node1 in partition:
                        node1_community = i
                    if node2 in partition:
                        node2_community = i
                if node1_community == node2_community:
                    continue
                
                # Calculează modularity gain dacă cele două noduri ar fi în aceeași comunitate
                delta_Q = 0
                for i, partition in enumerate(partitions):
                    for j, other_partition in enumerate(partitions):
                        if i == j:
                            delta_Q += G.subgraph(partition).number_of_edges() / (2 * G.number_of_edges()) \
                                       - np.power(sum(G.degree[partition]) / (2 * G.number_of_edges()), 2)
                        else:
                            delta_Q += G.subgraph(partition).number_of_edges() / (2 * G.number_of_edges()) \
                                       - np.power(sum(G.degree[partition]) / (2 * G.number_of_edges()), 2) \
                                       + 2 * G.subgraph(partition).number_of_edges_between(other_partition) / (2 * G.number_of_edges())
                
                # Verifică dacă modularity gain este pozitiv și face schimbări dacă este
                if delta_Q > 0:
                    partitions[node1_community].remove(node1)
                    partitions[node2_community].add(node1)
                    improvement = True
        
        # Ieși dacă nu mai există îmbunătățiri
        if not improvement:
            break
    
    return partitions


if __name__ == '__main__':
    # Incarcarea datelor problemei
    edges = [(1, 1), (2, 2), (3, 1), (4, 1), (5, 1), (6, 2), (7, 2), (8, 2), (9, 1), (10, 2), (11, 1), (12, 1), (13, 1), (14, 2), (15, 1), (16, 1), (17, 1), (18, 2), (19, 1), (20, 2), (21, 1), (22, 1), (23, 2), (24, 1), (25, 1), (26, 2), (27, 2), (28, 2), (29, 1), (30, 1), (31, 1), (32, 2), (33, 2), (34, 1), (35, 1), (36, 1), (37, 1), (38, 1), (39, 1), (40, 1), (41, 1), (42, 2), (43, 1), (44, 1), (45, 1), (46, 1), (47, 1), (48, 1), (49, 2), (50, 1), (51, 1), (52, 1), (53, 1), (54, 1), (55, 2), (56, 1), (57, 2), (58, 2), (59, 1), (60, 1), (61, 2), (62, 1)]


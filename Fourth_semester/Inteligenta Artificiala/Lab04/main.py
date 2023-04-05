from chromosome2 import MyChromosome
from genetic_algorithm import GA
from utils import readGraphFromFile, calculateDistance, calculateDistanceCyclic


def travelingSalesman(graph, population_size=500, no_of_generations=100, evaluation_function=calculateDistanceCyclic, chromosome=MyChromosome):

    # sunt preluati parametrii unui algoritm genetic
    genetic_parameters = {
        "popSize": population_size,
        "noGen": no_of_generations,
        "function": evaluation_function,
        "chromosome": chromosome
    }
    problem_parameters = graph
    problem_parameters["function"] = evaluation_function
    ga = GA(genetic_parameters, problem_parameters)
    ga.initialisation()
    ga.evaluation()
    bests = []
    last_gens = []

    # iteram prin fiecare generație a algoritmului genetic, cu diferite moduri de selecție, cum ar fi elitism, steady-state sau one-generation.
    for generation in range(genetic_parameters["noGen"]):
        # ga.oneGeneration()
        ga.oneGenerationElitism()
        # ga.oneGenerationSteadyState()
        best_chromosome = ga.bestChromosome()
        last_gens = ga.population
        bests.append(best_chromosome)

    # generatia ca mai buna este cu drumul cel mai scurt
    the_best = bests[0]
    for best in bests:
        if best.fitness > the_best.fitness:
            the_best = best

    the_bests = [the_best]

    for candidate in last_gens:
        if candidate.fitness == the_best.fitness and candidate not in the_bests:
            the_bests.append(candidate)

    return the_bests

# reprezentare matrice de adiacenta ponderata
if __name__ == "__main__":
    graph = readGraphFromFile("data/hard_02.txt")
    result = travelingSalesman(graph, 1000, 500)
    for res in result:
        print(res)

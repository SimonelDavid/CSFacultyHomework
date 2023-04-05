from random import randint


class GA:
    def __init__(self, param=None, problem_parameters=None):
        self.__param = param
        self.__problem_parameters = problem_parameters
        self.__population = []

    @property
    def population(self):
        return self.__population

    def initialisation(self):
        for _ in range(0, self.__param['popSize']):
            c = self.__param["chromosome"](self.__problem_parameters)
            self.__population.append(c)

    def evaluation(self):
        for c in self.__population:
            c.fitness = self.__problem_parameters['function'](self.__problem_parameters, c.representation)

    def bestChromosome(self):
        best = self.__population[0]     # initializarea variabilei best cu primul cromozom din populatie

        # pentru fiecare cromozom din populație, se verifică dacă valoarea de fitness a acestuia este mai mică decât valoarea de fitness a cromozomului stocat în variabila best
        for c in self.__population:
            if c.fitness < best.fitness:
                best = c
        
        # se returnează cromozomul cu cea mai mică valoare de fitness (cel mai bun cromozom)
        return best

    def worstChromosome(self):
        best = self.__population[0]
        for c in self.__population:
            if c.fitness > best.fitness:
                best = c
        return best

    def selection(self):
        pos1 = randint(0, self.__param['popSize'] - 1)
        pos2 = randint(0, self.__param['popSize'] - 1)
        if self.__population[pos1].fitness < self.__population[pos2].fitness:
            return pos1
        else:
            return pos2

    # Metoda oneGeneration realizează o selecție aleatoare a părinților și crează o nouă generație pe baza lor, fără a păstra cel mai bun cromozom din generația precedentă.
    def oneGeneration(self):
        newPop = []
        for _ in range(self.__param['popSize']):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            off = p1.crossover(p2)
            off.mutation()
            newPop.append(off)
        self.__population = newPop
        self.evaluation()

    # Metoda oneGenerationElitism utilizează și o selecție aleatoare a părinților, dar păstrează cel mai bun cromozom din generația precedentă, 
    # asigurând astfel că soluția optimă nu va fi pierdută.
    def oneGenerationElitism(self):
        newPop = [self.bestChromosome()]
        for _ in range(self.__param['popSize'] - 1):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            off = p1.crossover(p2)
            off.mutation()
            newPop.append(off)
        self.__population = newPop
        self.evaluation()

    # Metoda oneGenerationSteadyState alege doi cromozomi părinți prin selecție aleatoare și creează un copil prin crossover și mutație. 
    # Acest copil înlocuiește cel mai rău cromozom din generația curentă.
    def oneGenerationSteadyState(self):
        for _ in range(self.__param['popSize']):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            off = p1.crossover(p2)
            off.mutation()
            off.fitness = self.__problem_parameters['function'](off.repres)
            worst = self.worstChromosome()
            if off.fitness < worst.fitness:
                worst = off
//
//  AlgorithmGenetic.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-26.
//
//

#include "AlgorithmGenetic.h"
AlgorithmGenetic::AlgorithmGenetic(const Problem& problem, int nb_eval_max, int population_size, double mutation_probability, double born_probability, int tournament_size):
Algorithm(problem, nb_eval_max),
_population_size(population_size),
_mutation_probability(mutation_probability),
_born_probability(born_probability),
_tournament_size(tournament_size) {
    
    _children_population_size = (int)ceil(_born_probability*_population_size);
}

bool compareIndividual(const Individual* a, const Individual* b) {
    return a->getObjective() < b->getObjective();
}

Solution* AlgorithmGenetic::run() {
    std::vector<Individual*> children_population;
    children_population.resize(_children_population_size);
    
    std::sort(_population.begin(), _population.end(), compareIndividual);
    Individual* best = _population[0];
    
    
    
    return best;
}

void AlgorithmGenetic::evaluate(Solution* solution) {
    Individual* individual = (Individual*)solution;
    
    std::vector<bool> chromosome = individual->getChromosome();
    int objective_function = 0;
    
    for (unsigned int i=0; i < chromosome.size(); i++) {
        if (chromosome[i]) {
            for (unsigned int j=0; j < _problem.getCover(i).size(); j++) {
                objective_function += _problem.getCost(_problem.getCover(i)[j]);
            }
        }
    }
    
    _cpt_eval++;
    individual->setObjective(objective_function);
}
//
//  Individual.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-26.
//
//

#include "Individual.h"

Individual::Individual(int default_value, int chromosome_size):
Solution(default_value) {
    _chromosome.resize(chromosome_size);
}


Individual::Individual(const Individual& individual):
Solution(individual),
_chromosome(individual._chromosome) {}

Individual& Individual::operator=(const Individual & individual) {
    if (&individual != this) {
        _chromosome = individual._chromosome;
    }
    
    return *this;
}


Individual* Individual::clone() const {
    return new Individual(*this);
}

Individual::~Individual() {
    _chromosome.clear();
}
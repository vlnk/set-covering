#include "AlgorithmRandom.h"

AlgorithmSimpleLocalSearch::AlgorithmSimpleLocalSearch(ProblemSetCovering* pb, int nb_eval_max, double pivot):
Algorithm(pb, nb_eval_max) {
    _current = new SimpleSolution(initializeSolution());
    
    double K = _problem->getNumOfSubsets() / pivot;
    _neighbours.resize(K);
    
    for (int k = 0; k < K; k++) {
        _neighbours[k] = new SimpleSolution(*_initial);
    }
}

AlgorithmSimpleLocalSearch::~AlgorithmSimpleLocalSearch() {
    delete _initial;
    delete _current;
    
    for (auto it = _neighbours.begin(); it != _neighbours.end(); it++) {
        delete (*it);
    }
    
    _neighbours.clear();
}

const SimpleSolution& AlgorithmSimpleLocalSearch::run() {
    //initialization
    SimpleSolution next(*_initial);
    
    //algorithm runtime
    do {
        next = getNeighbour();

        if (next < *_current ) {
            *_current = next;
        }
        
    } while (_cpt_eval < _nb_eval_max);
    
    return *_current;
}

const SimpleSolution& AlgorithmSimpleLocalSearch::initializeSolution() {
    _initial = new SimpleSolution(0, *_problem);
    
    while (!_initial->validate(*_problem)) {
        int random_subset = rand() % _problem->getNumOfSubsets();
        
        _initial->addSubset(random_subset, *_problem);
    }
    
    return *_initial;
}

const int AlgorithmSimpleLocalSearch::estimate(const SimpleSolution& s) {
    
    int objective_function = 0;
    _cpt_eval++;
    
    for (int i = 0; i < _problem->getNumOfSubsets(); i++) {
        
        if (s.isSubsetAccepted(i)) {
            objective_function += _problem->getCost(i);
        }
    }
    
    return objective_function;
}

const SimpleSolution& AlgorithmSimpleLocalSearch::getNeighbour() {
    int best_objective = std::numeric_limits<int>::infinity();
    
    for (auto it = _neighbours.begin(); it != _neighbours.end(); it++) {
        (**it) = *_current;
    }
    
    int k = 0;
    int index_best = 0;
    
    do {
        int flip = orientateNeighbourhood(*_neighbours[k]);
        
        _neighbours[k]->removeSubset(flip, *_problem);
        repair(*_neighbours[k]);
        _neighbours[k]->setObjective(estimate(*_neighbours[k]));
        
        if (_neighbours[k]->getObjective() < best_objective) {
            best_objective = _neighbours[k]->getObjective();
            index_best = k;
        }
        
        k++;
        
    } while (k < _neighbours.size());
    
    return *_neighbours[index_best];
}

const int AlgorithmSimpleLocalSearch::orientateNeighbourhood(const SimpleSolution& sol) {
    int random_delete;
    
    do {
        random_delete = rand() % _problem->getNumOfSubsets();
    } while (!sol.isSubsetAccepted(random_delete));
    
    return random_delete;
}

void AlgorithmSimpleLocalSearch::repair(SimpleSolution & sol) {
    while (!sol.validate(*_problem)) {
        sol.addSubset(rand() % _problem->getNumOfSubsets(), *_problem);
    }
}


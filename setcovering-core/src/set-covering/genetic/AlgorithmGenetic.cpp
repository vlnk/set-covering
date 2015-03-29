#include "AlgorithmGenetic.h"

AlgorithmGenetic::AlgorithmGenetic(ProblemSetCovering* p, int nb_max_eval, const unsigned int& seed, int population_size, double mu, double sdd) :
Algorithm<Individual, ProblemSetCovering>(p, nb_max_eval, "genetic", seed),
_population_size(population_size),
_setting_diffirence_degree(sdd),
_penalty(p->getMaxCost()){
    
    if (mu < 0 || mu > 1) {
        throw std::invalid_argument("error: the mu parameter is not correct.");
    }
    else {
        _mu = mu;
    }
    
    _population.resize(population_size);
}

AlgorithmGenetic::~AlgorithmGenetic() {
    for (auto it = _population.begin(); it != _population.end(); it++) {
        if (*it) delete *it;
    }
    
    _population.clear();
}

bool compareIndividu(Individual* a, Individual* b)  {
    return a->getObjective() < b->getObjective();
}

const Individual& AlgorithmGenetic::run() {
    
    initializePopulation(std::numeric_limits<int>::infinity());
    
    std::sort(_population.begin(), _population.end(), compareIndividu);
    _current = static_cast<Individual*>(_population[0]->clone());
    
    std::vector<Individual*> children;
    std::vector<Individual*> mutants;
    
    do {
        while (children.size() + mutants.size() < _population.size()) {
            std::uniform_int_distribution<int> dist(0, _population_size - 1);
            
            int index_mother = dist(_rng);
            int index_father = dist(_rng);
            
            Individual* mother = _population[index_mother];
            Individual* father = _population[index_father];
                
            double differenceDegree = getDifferenceDegree(*mother, *father);
                
            if (canChange(differenceDegree > _setting_diffirence_degree)) {
                children.push_back(crossover(*mother, *father));
            }
            else if (canChange(differenceDegree < _setting_diffirence_degree)) {
                mutants.push_back(mutation(*father, dist(_rng) % 5));
            }
        }
        
        renewPopulation(children, mutants);
        
        if (_population[0]->getObjective() < _current->getObjective()) {
            *_current = *_population[0];
        }
        
        children.clear();
        mutants.clear();
        
        decreaseSettingDifferenceDegree();
        
    } while (_cpt_eval < _nb_eval_max);
    
    return *_current;
}

const int AlgorithmGenetic::estimate(const Individual& ind) {
    int objective_function = 0;
    _cpt_eval++;
    
    for (int i = 0; i < _problem->getNumOfSubsets(); i++) {
        
        if (ind.getGeneX(i)) {
            objective_function += _problem->getCost(i);
        }
    }
    
    return objective_function + getPenaltyRate(ind)*_penalty;
}

const int AlgorithmGenetic::getPenaltyRate(const Individual& ind) {
    int penalty_rate = 0;
    
    for (unsigned int i = 0; i < _problem->getNumOfElements(); i++) {
        if (!ind.isCovered(i)) penalty_rate++;
    }
    
    return penalty_rate;
}

Individual* AlgorithmGenetic::getRandomIndividual(int default_value) {
    Individual* initial = new Individual(default_value, *_problem);
    
    while (!initial->validate(*_problem)) {
        int random_subset = rand() % _problem->getNumOfSubsets();
        
        initial->addSubset(random_subset, *_problem);
    }
    
    initial->setObjective(estimate(*initial));
    return initial;
}

void AlgorithmGenetic::initializePopulation(int default_value) {
    for (int i = 0; i < _population.size(); i++) {
        _population[i] = getRandomIndividual(0);
    }
}

Individual* AlgorithmGenetic::mutation(const Individual& input, const int& num_of_mutations) {
    Individual* mutant = new Individual(input);
    
    std::vector<int> uncovered_elements;
    for (int i = 0; i < _problem->getNumOfElements(); i++) {
        if (!mutant->isCovered(i)) {
            uncovered_elements.push_back(i);
        }
    }
    
    std::vector<int> covered_elements;
    for (int i = 0; i < _problem->getNumOfElements(); i++) {
        if (mutant->getGeneY(i) > 1) {
            covered_elements.push_back(i);
        }
    }
    
    long range_long = uncovered_elements.size() + covered_elements.size();
    
    if (range_long != 0) {
        int rand_int = static_cast<int>(range_long);
        std::uniform_int_distribution<int> dist(0, rand_int - 1);
        
        for (int k = 0; k < num_of_mutations; k++) {
            int rand = dist(_rng);
            
            if (uncovered_elements.size() != 0 && rand < uncovered_elements.size()) {
                
                int candidate = _problem->getSmallerCoveredSubset(rand);
                mutant->addSubset(candidate, *_problem);
                
            }
            else
            {
                int candidate = _problem->getLargerCoveredSubset(rand);
                mutant->removeSubset(candidate, *_problem);
            }
        }
    }
    
    
    
    
    mutant->setObjective(estimate(*mutant));
    
    return mutant;
}

Individual* AlgorithmGenetic::crossover(const Individual& mother, const Individual& father) {
    std::uniform_int_distribution<int> dist(0, _problem->getNumOfSubsets());

    //int cutting_point_mother = dist(_rng);
    //int cutting_point_father = cutting_point_mother + dist(_rng);
    
    int cutting_point = std::abs(dist(_rng));
    
    /*
    if (cutting_point_mother < cutting_point_father) {
        std::swap(cutting_point_father, cutting_point_mother);
    }
    */
    Baby_t baby(*_problem);
    
    //baby.copyCh(mother, 0, cutting_point_mother);
    //baby.copyCh(father, cutting_point_mother, cutting_point_father);
    //baby.copyCh(mother, cutting_point_father, _problem->getNumOfSubsets());
    
    baby.copyCh(mother, 0, cutting_point);
    baby.copyCh(father, cutting_point, _problem->getNumOfSubsets());
    
    Individual* child = new Individual(std::numeric_limits<int>::infinity(), baby.chX, baby.chY);
    child->setObjective(estimate(*child));
    
    return child;
}

const bool AlgorithmGenetic::canChange(const bool& can_change) {
    bool canI = false;
    
    if (can_change) {
        canI = true;
    }
    else {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double random = dist(_rng);
        
        if (random >= 0.5) canI = true;
    }
    
    return canI;
}

void AlgorithmGenetic::Baby_t::copyCh(const Individual& parent, const int& begin, const int& end) {
    
    for (int i = begin; i < end; ++i) {
        chX[i] = parent.getGeneX(i);
        
        for (int j = 0; j < chY.size(); ++j) {
            if (chX[i] && problem.getElement(j)[i]) {
                chY[j] = true;
            }
        }
    }
}

void AlgorithmGenetic::renewPopulation(const std::vector<Individual*>& children, const std::vector<Individual*>& mutants) {
    std::vector<Individual*> full_population;
    
    for (auto it = _population.begin(); it !=_population.end(); it++) {
        full_population.push_back(*it);
    }
    
    for (auto it = children.begin() ; it != children.end(); it++) {
        full_population.push_back(*it);
    }
    
    for (auto it = mutants.begin() ; it != mutants.end(); it++) {
        full_population.push_back(*it);
    }
    
    _population.clear();
    
    std::sort(full_population.begin(), full_population.end(), compareIndividu);
    
    int i = 0;
    while (i < _population_size) {
        _population.push_back(new Individual(*full_population[i]));
        i++;
    }
    
    while (i < full_population.size()) {
        delete full_population[i];
        i++;
    }
}

const double AlgorithmGenetic::getDifferenceDegree(const Individual & mother, const Individual& father) const {
    double differenceDegree = 0;
    
    for (unsigned int i = 0; i < _problem->getNumOfSubsets(); i++) {
        if (mother.getGeneX(i) != father.getGeneX(i)) {
            differenceDegree++;
        }
    }
    
    return differenceDegree/_problem->getNumOfSubsets();
}

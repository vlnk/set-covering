//
//  AlgorithmGenetic.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-03-27.
//
//

#ifndef __setcovering_core__AlgorithmGenetic__
#define __setcovering_core__AlgorithmGenetic__

#include <stdio.h>
#include "../ProblemSetCovering.h"
#include "Individual.h"
#include "../../framework/Algorithm.h"

class AlgorithmGenetic : public Algorithm<Individual, ProblemSetCovering> {
private:
    std::vector<Individual*> _population;
    
    int _population_size;
    double _mu;
    int _penalty;
    double _setting_diffirence_degree;
    
    struct Baby_t {
        std::vector<bool> chX;
        std::vector<int> chY;
        const ProblemSetCovering& problem;
        
        Baby_t(const ProblemSetCovering& p):
        problem(p),
        chX(p.getNumOfSubsets(), false),
        chY(p.getNumOfElements(), 0) {}
        
        void copyCh(const Individual&, const int&, const int&);
    };
    
public:
    AlgorithmGenetic(ProblemSetCovering*, int, const unsigned int&, int, double, double);
    ~AlgorithmGenetic();
    
    const int estimate(const Individual&);
    const Individual& run();
    
private:
    Individual* crossover(const Individual&, const Individual&);
    Individual* mutation(const Individual&, const int&);
    void renewPopulation(const std::vector<Individual*>&, const std::vector<Individual*>&);
    
    const int getPenaltyRate(const Individual&);
    
    void decreaseSettingDifferenceDegree() {
        _setting_diffirence_degree = _mu*_setting_diffirence_degree;
    }
    
    void initializePopulation(int);
    Individual* getRandomIndividual(int);
    
    const bool canChange(const bool&);
    const double getDifferenceDegree(const Individual & mother, const Individual& father) const;
    
    friend std::ostream& operator << (std::ostream& output, const AlgorithmGenetic& alg) {
        output << static_cast<const Algorithm<Individual, ProblemSetCovering>&>(alg);
        
        output << "population size: " << alg._population_size << std::endl;
        output << "mu: " << alg._mu << std::endl;
        output << "initial setting difference degree: " << alg._setting_diffirence_degree << std::endl;
        return output;
    }
};

#endif /* defined(__setcovering_core__AlgorithmGenetic__) */

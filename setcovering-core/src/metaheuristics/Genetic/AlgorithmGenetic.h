//
//  AlgorithmGenetic.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-26.
//
//

#ifndef __setcovering_core__AlgorithmGenetic__
#define __setcovering_core__AlgorithmGenetic__

#include <stdio.h>
#include <cmath>

#include "../Algorithm.h"
#include "Individual.h"

class AlgorithmGenetic : public Algorithm {
private:
    int _population_size;
    double _mutation_probability;
    double _born_probability;
    int _tournament_size;
    int _children_population_size;
    
    std::vector<Individual*> _population;
    
public:
    AlgorithmGenetic(const Problem&, int = 10000, int = 10, double = 0.1, double = 0.1, int = 3);
    
    Solution* run();
    void evaluate(Solution*);
};

#endif /* defined(__setcovering_core__AlgorithmGenetic__) */

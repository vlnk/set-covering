//
//  Individual.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-03-27.
//
//

#ifndef __setcovering_core__Individual__
#define __setcovering_core__Individual__

#include <stdio.h>
#include "../SolutionSetCovering.h"
#include "../ProblemSetCovering.h"

class Individual : public SolutionSetCovering {
public:
    Individual(int, const ProblemSetCovering&);
    Individual(int, std::vector<bool>&, std::vector<int>&);
    ~Individual() {};
    
    const bool getGeneX(const int i) const { return _accepted_subsets[i]; }
    const int getGeneY(const int i) const { return _covered_elements[i]; }
    
    bool operator==(const Individual& other) const
    {
        return _objective_function == other.getObjective();
    }
};

#endif /* defined(__setcovering_core__Individual__) */

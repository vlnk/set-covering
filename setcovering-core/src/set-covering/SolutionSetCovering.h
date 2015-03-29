//
//  SolutionSetCovering.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-03-27.
//
//

#ifndef __setcovering_core__SolutionSetCovering__
#define __setcovering_core__SolutionSetCovering__

#include <stdio.h>
#include "../framework/Solution.h"
#include "ProblemSetCovering.h"

class SolutionSetCovering : public Solution<ProblemSetCovering> {
protected:
    std::vector<bool> _accepted_subsets;
    std::vector<int> _covered_elements;
        
public:
    SolutionSetCovering(int, int, int);
    SolutionSetCovering(int, const ProblemSetCovering&);
    SolutionSetCovering(int, std::vector<bool>&, std::vector<int>&);
        
    virtual ~SolutionSetCovering();
    SolutionSetCovering(const SolutionSetCovering&);
    SolutionSetCovering& operator= (const SolutionSetCovering&);
    SolutionSetCovering* clone() const { return new SolutionSetCovering(*this); }
        
    const bool validate(const ProblemSetCovering&) const;
    
    const bool isCovered(const int& index) const { return (_covered_elements[index] > 0); }
    
    void addSubset(const int, const ProblemSetCovering&);
    void removeSubset(const int, const ProblemSetCovering&);
    const int countCovers(const int, const ProblemSetCovering&);
};

#endif /* defined(__setcovering_core__SolutionSetCovering__) */

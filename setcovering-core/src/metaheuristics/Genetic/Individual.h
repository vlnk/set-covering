//
//  Individual.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-26.
//
//

#ifndef __setcovering_core__Individual__
#define __setcovering_core__Individual__

#include <stdio.h>
#include <vector>
#include "../Solution.h"

class Individual: public Solution {
private:
    std::vector<bool> _chromosome;
    
public:
    Individual(int, int);
    
    const std::vector<bool>& getChromosome() const { return _chromosome; }
    
    ~Individual();
    Individual(const Individual&);
    Individual* clone() const;
    Individual& operator= (const Individual&);
};

#endif /* defined(__setcovering_core__Individual__) */

//
//  Algorithm.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#ifndef __setcovering_core__Algorithm__
#define __setcovering_core__Algorithm__

#include <stdio.h>
#include "../core/Problem.h"
#include "Solution.h"

class Algorithm {
protected:
    int _nb_eval_max;
    int _cpt_eval;
    const Problem _problem;
    
public:
    Algorithm(const Problem&, int = 10000);
    
    virtual Solution* run() = 0;
    virtual void evaluate(Solution*) = 0;
    virtual ~Algorithm() {};
};

#endif /* defined(__setcovering_core__Algorithm__) */

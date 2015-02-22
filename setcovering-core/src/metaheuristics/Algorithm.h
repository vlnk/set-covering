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
#include "Instance.h"

class Algorithm {
protected:
    int nbEvalMax;
    
public:
    Algorithm(const Instance instance);
    virtual ~Algorithm() {};
};

#endif /* defined(__setcovering_core__Algorithm__) */

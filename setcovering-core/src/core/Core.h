//
//  Core.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#ifndef __setcovering_core__Core__
#define __setcovering_core__Core__

#include <stdio.h>

#include "InputChecker.h"
#include "../framework/Algorithm.h"

class Core {
private:
    Algorithm& _algorithm;
    
public:
    Core(Algorithm& algorithm);
    ~Core();
};

#endif /* defined(__setcovering_core__Core__) */

//
//  Solution.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#ifndef __setcovering_core__Solution__
#define __setcovering_core__Solution__

#include <stdio.h>

class Solution {
private:
    double _objective_function;
    
public:
    double getObjective() const { return _objective_function; }
    void setObjective(int objective_function) { _objective_function = objective_function; }
    
    Solution(int);
    virtual ~Solution();
    
    Solution(const Solution&);
    virtual Solution* clone() const = 0;
    Solution& operator= (const Solution&);
    
};

#endif /* defined(__setcovering_core__Solution__) */

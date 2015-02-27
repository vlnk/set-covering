//
//  Solution.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#include "Solution.h"

Solution::Solution(int default_value):
_objective_function(default_value) {}

Solution::Solution(const Solution& solution):
_objective_function(solution.getObjective()) {}

Solution& Solution::operator=(const Solution& solution) {
    if (&solution != this) {
        _objective_function = solution.getObjective();
    }
    
    return *this;
}

Solution::~Solution() {};
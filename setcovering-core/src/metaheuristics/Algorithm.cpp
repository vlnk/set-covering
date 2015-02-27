//
//  Algorithm.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#include "Algorithm.h"
#include "../core/Problem.h"

Algorithm::Algorithm(const Problem& problem, int nb_eval_max) :
    _problem(problem),
    _nb_eval_max(nb_eval_max),
    _cpt_eval(0) {}
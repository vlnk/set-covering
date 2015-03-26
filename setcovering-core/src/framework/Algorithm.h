//
//  Algorithm.h
#ifndef __setcovering_core__Algorithm__
#define __setcovering_core__Algorithm__

#include <stdio.h>
#include "Problem.h"
#include "Solution.h"

template <typename T, typename U>
class Algorithm {
protected:
    int _nb_eval_max;
    int _cpt_eval;
    
    U* _problem;
    T* _current;
    T* _initial;
    
public:
    Algorithm(U* p, int eval_max):
    _problem(p),
    _nb_eval_max(eval_max),
    _cpt_eval(0),
    _current(nullptr),
    _initial(nullptr) {};
    
    virtual const T& run() = 0;
    virtual ~Algorithm() {};
    
    virtual const int estimate(const T&) = 0;
    
    const T& getCurrent() const { return *_current; }
    const T& getInitial() const { return *_initial; }
};

#endif /* defined(__setcovering_core__Algorithm__) */

//
//  Algorithm.h
#ifndef __setcovering_core__Algorithm__
#define __setcovering_core__Algorithm__

#include <stdio.h>
#include <random>
#include "Problem.h"
#include "Solution.h"

template <typename T, typename U>
class Algorithm {
protected:
    std::string _name;
    int _nb_eval_max;
    int _cpt_eval;
    
    std::mt19937 _rng;
    
    U* _problem;
    T* _current;
    T* _initial;
    
public:
    Algorithm(U* p, int eval_max, std::string name, const unsigned int& seed):
    _name(name),
    _problem(p),
    _nb_eval_max(eval_max),
    _cpt_eval(0),
    _rng(seed),
    _current(nullptr),
    _initial(nullptr) {};
    
    virtual const T& run() = 0;
    virtual ~Algorithm() {};
    
    virtual const int estimate(const T&) = 0;
    
    const T& getCurrent() const { return *_current; }
    const T& getInitial() const { return *_initial; }
    
    friend std::ostream& operator << (std::ostream& output, const Algorithm<T, U>& alg) {
        output << "algorithm: " << alg._name << std::endl;
        output << "number of evaluation maximal: " << alg._nb_eval_max << std::endl;
        return output;
    }
};

#endif /* defined(__setcovering_core__Algorithm__) */

#ifndef __setcovering_core__Solution__
#define __setcovering_core__Solution__

#include <stdio.h>
#include <iostream>
#include "Problem.h"

template <typename T>
class Solution {
protected:
    double _objective_function;
    
public:
    double getObjective() const {
        return _objective_function;
    }
    
    void setObjective(int objective_function) {
        _objective_function = objective_function;
    }
    
    Solution(int default_value):
    _objective_function(default_value) {};
    
    virtual ~Solution() {};
    
    template<typename U>
    Solution(const Solution<U>&);
    
    virtual Solution<T>* clone() const = 0;
    
    template<typename U>
    Solution<U>& operator = (const Solution<U>&);
    
    virtual bool validate(const T&) const = 0;
    
    template<typename U>
    bool operator < (const Solution<U>& s) {
        if (_objective_function < s._objective_function) {
            return true;
        }
        else {
            return false;
        }
    }
    
    friend std::ostream& operator << (std::ostream& output, const Solution<T>& sol) {
        output << "SOLUTION" << std::endl;
        output << "objective function: " << sol._objective_function << std::endl;
        
        return output;
    }
};

#endif /* defined(__setcovering_core__Solution__) */

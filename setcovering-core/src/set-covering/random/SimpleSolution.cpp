#include "SimpleSolution.h"

SimpleSolution::SimpleSolution(int default_value, int num_of_sets, int num_of_elements):
Solution(default_value) {
    _accepted_subsets.resize(num_of_sets);
    _covered_elements.resize(num_of_elements);
    
    for (auto it = _accepted_subsets.begin(); it != _accepted_subsets.end(); it++) {
        *it = false;
    }
    
    for (auto it = _covered_elements.begin(); it != _covered_elements.end(); it++) {
        *it = false;
    }
}

SimpleSolution::SimpleSolution(int default_value, const ProblemSetCovering& pb):
SimpleSolution(default_value, pb.getNumOfSubsets(), pb.getNumOfElements()) {}

SimpleSolution::SimpleSolution(const SimpleSolution& simple):
Solution(simple),
_accepted_subsets(simple._accepted_subsets),
_covered_elements(simple._covered_elements) {}

SimpleSolution& SimpleSolution::operator = (const SimpleSolution & simple) {
    if (&simple != this) {
        _objective_function = simple._objective_function;
        _covered_elements = simple._covered_elements;
        _accepted_subsets = simple._accepted_subsets;
    }
    
    return *this;
}


SimpleSolution* SimpleSolution::clone() const {
    return new SimpleSolution(*this);
}

SimpleSolution::~SimpleSolution() {
    _covered_elements.clear();
    _accepted_subsets.clear();
}

bool SimpleSolution::validate(const ProblemSetCovering& pb) const {
    bool isValidate = true;
    
    for (int i = 0; i < pb.getNumOfElements(); i++) {
        if (!_covered_elements[i]) {
            isValidate = false;
            break;
        }
    }
    
    return isValidate;
}

void SimpleSolution::addSubset(const int subset_index, const ProblemSetCovering& p) {
    if (subset_index > _accepted_subsets.size()) {
        throw std::out_of_range("Bad subset index");
    }
    
    if (!_accepted_subsets[subset_index]) {
        _accepted_subsets[subset_index] = true;
        _objective_function += p.getCost(subset_index);
        
        std::vector<bool> subset = p.getSubset(subset_index);
        
        for (int i = 0; i < p.getNumOfElements(); i++) {
            if (subset[i]) {
                _covered_elements[i] = true;
            }
        }
    }
}

void SimpleSolution::removeSubset(const int subset_index, const ProblemSetCovering& p) {
    if (subset_index > _accepted_subsets.size()) {
        throw std::out_of_range("Bad subset index");
    }
    
    if (_accepted_subsets[subset_index]) {
        _accepted_subsets[subset_index] = false;
        _objective_function -= p.getCost(subset_index);
        
        std::vector<bool> subset = p.getSubset(subset_index);
        
        for (int i = 0; i < p.getNumOfElements(); i++) {
            if (subset[i] && getNumOfCovers(i, p) < 1) {
                _covered_elements[i] = false;
            }
        }
    }
}

const int SimpleSolution::getNumOfCovers(const int element_index, const ProblemSetCovering& p) {
    int numOfCovers = 0;
    std::vector<bool> element = p.getElement(element_index);
    
    if (_covered_elements[element_index]) {
        for (int j = 0; j < p.getNumOfSubsets(); j++) {
            if (element[j] && _accepted_subsets[j]) {
                numOfCovers++;
            }
            
            if (numOfCovers > 1) break;
        }
    }
    
    return numOfCovers;
}

void SimpleSolution::processTwoFlip(std::pair<int, int> twoFlip, const ProblemSetCovering& p) {
    
    removeSubset(twoFlip.first, p);
}



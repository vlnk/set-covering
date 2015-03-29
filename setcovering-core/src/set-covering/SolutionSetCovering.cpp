#include "SolutionSetCovering.h"

SolutionSetCovering::SolutionSetCovering(int default_value, int num_of_sets, int num_of_elements):
Solution(default_value),
_accepted_subsets(num_of_sets, false),
_covered_elements(num_of_elements, 0) {}

SolutionSetCovering::SolutionSetCovering(int default_value, std::vector<bool>& accepted, std::vector<int>& covered):
Solution(default_value),
_accepted_subsets(accepted),
_covered_elements(covered) {}

SolutionSetCovering::SolutionSetCovering(int default_value, const ProblemSetCovering& pb):
SolutionSetCovering(default_value, pb.getNumOfSubsets(), pb.getNumOfElements()) {}

SolutionSetCovering::SolutionSetCovering(const SolutionSetCovering& s):
Solution(s),
_accepted_subsets(s._accepted_subsets),
_covered_elements(s._covered_elements) {}

SolutionSetCovering& SolutionSetCovering::operator = (const SolutionSetCovering & s) {
    if (&s != this) {
        _objective_function = s._objective_function;
        _covered_elements = s._covered_elements;
        _accepted_subsets = s._accepted_subsets;
    }
    
    return *this;
}

SolutionSetCovering::~SolutionSetCovering() {
    _covered_elements.clear();
    _accepted_subsets.clear();
}

const bool SolutionSetCovering::validate(const ProblemSetCovering& pb) const {
    bool isValidate = true;
    
    for (int i = 0; i < pb.getNumOfElements(); i++) {
        if (!_covered_elements[i]) {
            isValidate = false;
            break;
        }
    }
    
    return isValidate;
}

void SolutionSetCovering::addSubset(const int subset_index, const ProblemSetCovering& p) {
    if (subset_index > _accepted_subsets.size()) {
        throw std::out_of_range("Bad subset index");
    }
    
    if (!_accepted_subsets[subset_index]) {
        _accepted_subsets[subset_index] = true;
        
        for (int i = 0; i < p.getNumOfElements(); i++) {
            if (p.getElement(i)[subset_index]) {
                _covered_elements[i]++;
            }
        }
    }
}

void SolutionSetCovering::removeSubset(const int subset_index, const ProblemSetCovering& p) {
    if (subset_index > _accepted_subsets.size()) {
        throw std::out_of_range("Bad subset index");
    }
    
    if (_accepted_subsets[subset_index]) {
        _accepted_subsets[subset_index] = false;
        
        for (int i = 0; i < p.getNumOfElements(); i++) {
            if (p.getElement(i)[subset_index]) {
                _covered_elements[i]--;
            }
        }
    }
}

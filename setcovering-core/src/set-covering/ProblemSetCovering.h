#ifndef __setcovering_core__ProblemSetCovering__
#define __setcovering_core__ProblemSetCovering__

#include <stdio.h>
#include "../framework/Problem.h"

class ProblemSetCovering : public Problem {
private:
    int _num_of_elements;
    int _num_of_subsets;
    
    std::vector<int> _costs;
    std::vector<std::vector<bool>> _covers_by_elements;
    
public:
    ProblemSetCovering(std::string, int, int, std::vector<int>, std::vector<std::vector<bool>>);
    ProblemSetCovering(std::string);
    ~ProblemSetCovering();
    
    int getNumOfElements() const { return _num_of_elements; }
    int getNumOfSubsets() const { return _num_of_subsets; }
    
    const std::vector<bool>& getElement(int element_index) const { return _covers_by_elements[element_index]; }
    const std::vector<bool> getSubset(int) const;
    int const getCost(int subset_index) const { return _costs[subset_index]; }
    
    const int getBestCoveredSubset(const int&) const;
    
    friend std::ostream& operator << (std::ostream& output, const ProblemSetCovering& pb);
    
private:
    int readCovers(std::vector<std::vector<int> >, std::vector<int> &, int);
    int readCosts(std::vector< std::vector<int> >, int);
    void setProblemMatrix(const std::vector< std::vector<int> >);
    void readInstance();
};

#endif /* defined(__setcovering_core__ProblemSetCovering__) */

#ifndef __setcovering_core__SimpleSolution__
#define __setcovering_core__SimpleSolution__

#include <vector>
#include <stdexcept>      // std::out_of_range
#include "../../framework/Solution.h"
#include "../ProblemSetCovering.h"

class SimpleSolution : public Solution<ProblemSetCovering> {
private:
    std::vector<bool> _accepted_subsets;
    std::vector<bool> _covered_elements;
    
public:
    SimpleSolution(int, int, int);
    SimpleSolution(int, const ProblemSetCovering&);
    
    ~SimpleSolution();
    SimpleSolution(const SimpleSolution&);
    SimpleSolution* clone() const;
    SimpleSolution& operator= (const SimpleSolution&);
    
    bool validate(const ProblemSetCovering&) const;
    void addSubset(const int, const ProblemSetCovering&);
    void removeSubset(const int, const ProblemSetCovering&);
    void processTwoFlip(std::pair<int, int>, const ProblemSetCovering&);
    
    const int getNumOfCovers(const int index_element, const ProblemSetCovering& pb);
    
    const bool isSubsetAccepted(const int subset_index) const { return _accepted_subsets[subset_index]; }
};

#endif /* defined(__setcovering_core__SimpleSolution__) */

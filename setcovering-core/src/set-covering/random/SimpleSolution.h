#ifndef __setcovering_core__SimpleSolution__
#define __setcovering_core__SimpleSolution__

#include <vector>
#include <stdexcept>      // std::out_of_range
#include "../SolutionSetCovering.h"
#include "../ProblemSetCovering.h"

class SimpleSolution : public SolutionSetCovering {
public:
    SimpleSolution(int d, const ProblemSetCovering p) : SolutionSetCovering(d,p) {};
    ~SimpleSolution() {};
    
    //void processTwoFlip(std::pair<int, int>, const ProblemSetCovering&);
    
    const bool isSubsetAccepted(const int subset_index) const { return _accepted_subsets[subset_index]; }
    const std::vector<bool> getAcceptedCover() const { return _accepted_subsets; }
};

#endif /* defined(__setcovering_core__SimpleSolution__) */

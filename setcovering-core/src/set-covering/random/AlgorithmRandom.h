#ifndef __setcovering_core__AlgorithmRandom__
#define __setcovering_core__AlgorithmRandom__

#include <stdio.h>
#include "../../framework/Algorithm.h"
#include "SimpleSolution.h"
#include "../ProblemSetCovering.h"

class AlgorithmSimpleLocalSearch : public Algorithm<SimpleSolution, ProblemSetCovering> {
private:
    std::vector<SimpleSolution*> _neighbours;
    
public:
    AlgorithmSimpleLocalSearch(ProblemSetCovering*, int, double);
    const SimpleSolution& run();
    
    const int estimate(const SimpleSolution&);
    const int estimate() { return estimate(*_current); }
    
    ~AlgorithmSimpleLocalSearch();
    
private:
    const SimpleSolution& getNeighbour();
    void repair(SimpleSolution&);
    std::pair<int, int> orientateNeighbourhoodFor2Flip();
    
    const SimpleSolution& initializeSolution();
};

#endif /* defined(__setcovering_core__AlgorithmRandom__) */

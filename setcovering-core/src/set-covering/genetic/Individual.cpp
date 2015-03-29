#include "Individual.h"

Individual::Individual(int d, const ProblemSetCovering& p):
SolutionSetCovering(d, p) {}

Individual::Individual(int default_value, std::vector<bool>& chX, std::vector<int>& chY):
SolutionSetCovering(default_value, chX, chY) {}
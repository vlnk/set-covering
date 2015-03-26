#include <iostream>
#include <stdexcept>
#include "core/InputChecker.h"
#include "set-covering/ProblemSetCovering.h"
#include "set-covering/random/AlgorithmRandom.h"
#include "set-covering/random/SimpleSolution.h"

int main(int argc, const char * argv[]) {
    
    srand (static_cast<unsigned int>(time(NULL)));
    InputChecker& checker = InputChecker::getInstance();
    
    try {
        
        bool can_execute = checker.readArguments(argc, argv);
        
        if (can_execute) {
            ProblemSetCovering pb(checker.getInstanceName());
            AlgorithmSimpleLocalSearch alg(&pb, 10000, pb.getNumOfSubsets()/3);
            SimpleSolution sol = alg.run();
            
            std::cout << sol.getObjective() << std::endl;
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::fstream::failure& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
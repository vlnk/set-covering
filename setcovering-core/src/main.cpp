#include <iostream>
#include <stdexcept>
#include "core/InputChecker.h"
#include "framework/Algorithm.h"
#include "set-covering/ProblemSetCovering.h"
#include "set-covering/random/AlgorithmRandom.h"
#include "set-covering/genetic/AlgorithmGenetic.h"

int main(int argc, const char * argv[]) {
    
    InputChecker& checker = InputChecker::getInstance();
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    try {
        
        bool can_execute = checker.readArguments(argc, argv);
        
        if (can_execute) {
            ProblemSetCovering pb(checker.getInstanceName());
            //AlgorithmSimpleLocalSearch alg(&pb, 10000, static_cast<unsigned int>(seed), pb.getNumOfSubsets()/3);
            AlgorithmGenetic alg(&pb, 100000, static_cast<unsigned int>(seed), 20, 0.9, 0.6);
            
            if (checker.isVerbose()) {
                std::cout << pb << std::endl;
                std::cout << alg << std::endl;
                //std::cout << "initial solution:" << std::endl << alg.getInitial() << std::endl;
            }
            
            SolutionSetCovering sol = alg.run();
            
            if (checker.isVerbose()) {
                std::cout << "final solution:" << std::endl << sol << std::endl;
            }
            else {
                std::cout << sol.getObjective() << std::endl;
            }
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
//
//  main.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-20.
//
//

#include <iostream>
#include <stdexcept>
#include "core/InputChecker.h"
#include "core/Problem.h"
#include "metaheuristics/genetic/AlgorithmGenetic.h"

int main(int argc, const char * argv[]) {
    
    InputChecker& checker = InputChecker::getInstance();
    
    try {
        
        bool can_execute = checker.readArguments(argc, argv);
        
        if (can_execute) {
            Problem* pb = new Problem(checker.getInstanceName());
            Algorithm* alg = new AlgorithmGenetic(*pb);
            
            std::cout << pb->getNumOfElements() << std::endl;
            std::cout << pb->getNumOfCovers() << std::endl;
        }
        
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
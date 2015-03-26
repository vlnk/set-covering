//
//  InputChecker.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#include "InputChecker.h"

InputChecker& InputChecker::getInstance() {
    static InputChecker instance;
    return instance;
}

bool InputChecker::readArguments(int argc, const char * argv[]) {
    std::vector<std::string> arguments(argv + 1, argv + argc);;
    bool can_execute = true;
    
    for (auto it = arguments.begin(); it != arguments.end(); it++) {
        if ((*it)[0] == '-') {
            if (it + 1 == arguments.end() && (*it).compare("-help") != 0) {
                throw std::invalid_argument("Argument for " + *it + " is empty");
            }
            
            if ((*it).compare("-help") == 0) {
                getHelp("setcovering-core","set covering");
                can_execute = false;
            }
            else if ((*it).compare("-alg") == 0) {
                if (it + 1 != arguments.end()) readAlgorithm(*(it + 1));
            }
            else if ((*it).compare("-in") == 0) {
                if (it + 1 != arguments.end()) _instance_name = *(it + 1);
            }
            else if ((*it).compare("-out") == 0) {
                if (it + 1 != arguments.end()) _report_name = *(it + 1);
            }
        }
    }
    
    return can_execute;
}

void InputChecker::readAlgorithm(const std::string algorithm_name) {
    std::string str;
    
    if (algorithm_name.compare("genetic") == 0) {
        _algorithm = _algorithms::GENETIC;
        str = "genetic";
    }
    else if (algorithm_name.compare("ant") == 0 ||
             algorithm_name.compare("colony") == 0) {
        _algorithm = _algorithms::ANT;
        str = "ant";
    }
    
    //std::cout << "The algorithm " << str << " is set" << std::endl;
}

void InputChecker::getHelp(const std::string prog_name, const std::string problem_name) {
    //int num_input = 4;
    
    std::cout << "OVERVIEW: a " + problem_name + " problem solver by metaheuristics" << std::endl;
    std::cout << "USAGE: " + prog_name + " [options] <inputs>" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    //std::cout << num_input << " inputs" << std::endl;
    std::cout << "\t -alg <algorithm>" << "\t Set a specific algorithm for the solver" << std::endl;
    std::cout << "\t -instance <file>" << "\t Load the instance file" << std::endl;
    std::cout << "\t -help" << "\t\t\t\t Give help" << std::endl;
    std::cout << std::endl;
}
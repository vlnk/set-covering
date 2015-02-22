//
//  main.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-20.
//
//

#include <iostream>
#include "InputChecker.h"

int main(int argc, const char * argv[]) {
    
    InputChecker& checker = InputChecker::getInstance();
    Instance * probleme = checker.readInstance(argv[1]);
    
    delete probleme;
    std::cout << "Hello, World!\n";
    return 0;
}

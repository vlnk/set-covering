//
//  InputChecker.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#ifndef __setcovering_core__InputChecker__
#define __setcovering_core__InputChecker__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Instance.h"

class InputChecker {
private:
    InputChecker() {};
    ~InputChecker() {};
    
    InputChecker& operator= (const InputChecker) = delete;
    InputChecker(const InputChecker&) = delete;
    
    int readCovers(std::vector<std::vector<int> > all_integers, std::vector<int> &cover, int starting_line);
    int readCosts(std::vector< std::vector<int> > all_integers, std::vector<int>& costs, int num_of_columns, int starting_line);
    
public:
    static InputChecker& getInstance();
    
    Instance* readInstance(std::string instanceName);
};


#endif /* defined(__setcovering_core__InputChecker__) */

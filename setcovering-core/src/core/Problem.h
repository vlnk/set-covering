//
//  Instance.h
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#ifndef __setcovering_core__Instance__
#define __setcovering_core__Instance__

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Problem {
private:
    std::string _name;
    
    int _num_of_elements;
    int _num_of_covers;
    
    std::vector<int> _costs;
    std::vector<std::vector<int>> _covers;
    
public:
    Problem(std::string, int, int, std::vector<int>, std::vector<std::vector<int>>);
    Problem(std::string);
    ~Problem();
    
    int getNumOfElements() { return _num_of_elements; }
    int getNumOfCovers() const { return _num_of_covers; }
    
    const std::vector<int>& getCover(int cover_index) const { return _covers[cover_index]; }
    int const getCost(int element_index) const { return _costs[element_index]; }
    
private:
    int readCovers(std::vector<std::vector<int> >, std::vector<int> &, int);
    int readCosts(std::vector< std::vector<int> >, std::vector<int>& , int);
    void readInstance();
};

#endif /* defined(__setcovering_core__Instance__) */

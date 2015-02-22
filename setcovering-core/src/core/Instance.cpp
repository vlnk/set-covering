//
//  Instance.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#include "Instance.h"

Instance::Instance(std::string fileName, std::vector<int> costs, std::vector<std::vector<int>> covers) :
    _name(fileName),
    _costs(costs),
    _covers(covers) {}

Instance::~Instance() {
    _costs.clear();
    
    for (auto it = _covers.begin(); it != _covers.end(); it++) {
        (*it).clear();
    }
    
    _covers.clear();
}
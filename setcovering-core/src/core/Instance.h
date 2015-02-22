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

class Instance {
private:
    std::string _name;
    std::vector<int> _costs;
    std::vector<std::vector<int>> _covers;
    
public:
    Instance(std::string fileName, std::vector<int> costs, std::vector<std::vector<int>> covers);
    ~Instance();
};

#endif /* defined(__setcovering_core__Instance__) */

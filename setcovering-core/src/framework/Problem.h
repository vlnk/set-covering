#ifndef __setcovering_core__Instance__
#define __setcovering_core__Instance__

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Problem {
protected:
    std::string _name;
    
public:
    Problem(std::string);
    virtual ~Problem() {};
    
    friend std::ostream& operator << (std::ostream& output, const Problem& pb);
private:
    virtual void readInstance() = 0;
};

#endif /* defined(__setcovering_core__Instance__) */

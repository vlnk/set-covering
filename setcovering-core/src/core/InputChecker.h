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
#include <vector>
#include <stdexcept>

#include <fstream>
#include <iostream>
#include <sstream>

class InputChecker {
private:
    enum _algorithms {GENETIC=0, ANT=1};
    
    int _algorithm;
    bool _isReportSpecified;
    bool _isVerboseActive;
    std::string _instance_name;
    std::string _report_name;
    
    InputChecker() : _algorithm(0), _isReportSpecified(false), _isVerboseActive(false) {};
    ~InputChecker() {};
    
    InputChecker& operator= (const InputChecker) = delete;
    InputChecker(const InputChecker&) = delete;
    
public:
    static InputChecker& getInstance();

    bool readArguments(int, const char * argv[]);
    void readAlgorithm(const std::string);
    
    void getHelp(const std::string, const std::string);
    const std::string& getInstanceName() const { return _instance_name; }
    
    const bool isVerbose() const { return _isVerboseActive; }
    const bool isReportSpecify() const { return _isReportSpecified; }
};


#endif /* defined(__setcovering_core__InputChecker__) */

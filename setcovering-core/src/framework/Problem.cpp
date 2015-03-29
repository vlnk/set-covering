#include "Problem.h"

Problem::Problem(std::string file_name):
_name(file_name) {}

std::ostream& operator << (std::ostream& output, const Problem& pb) {
    output << "instance name: " << pb._name << std::endl;
    return output;
}
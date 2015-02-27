//
//  Instance.cpp
//  setcovering-core
//
//  Created by Valentin Laurent on 2015-02-21.
//
//

#include "Problem.h"

Problem::Problem(std::string file_name, int num_of_elements, int num_of_covers, std::vector<int> costs, std::vector<std::vector<int>> covers):
_name(file_name),
_num_of_elements(num_of_elements),
_num_of_covers(num_of_covers),
_costs(costs),
_covers(covers) {}

Problem::Problem(std::string file_name):
_name(file_name) {
    readInstance();
}

Problem::~Problem() {
    _costs.clear();
    
    for (auto it = _covers.begin(); it != _covers.end(); it++) {
        (*it).clear();
    }
    
    _covers.clear();
}

void Problem::readInstance() {
    
    std::ifstream file;
    file.exceptions(std::ifstream::failbit);
    
    std::vector<int> costs;
    std::vector<std::vector<int>> covers;
    
    try {
        file.open(_name);
        
        std::string line;
        std::vector< std::vector<int> > all_integers;
        
        while ( getline(file, line ) ) {
            std::istringstream is( line );
            all_integers.push_back(
                                   std::vector<int>(std::istream_iterator<int>(is),
                                                    std::istream_iterator<int>() ) );
        }
        
        int last_line_parsed = 0;
        
        _num_of_covers = all_integers[0][0];
        _num_of_elements = all_integers[0][1];
        
        covers.resize(_num_of_covers);
        
        last_line_parsed++;
        
        last_line_parsed = readCosts(all_integers, costs, last_line_parsed);
        
        for (int i = 0; i < _num_of_covers; i++) {
            last_line_parsed = readCovers(all_integers, covers[i], last_line_parsed);
        }
        
        file.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << _name << " path is invalid!" << std::endl;
    }
}

int Problem::readCosts(std::vector< std::vector<int> > all_integers, std::vector<int>& costs, int starting_line) {
    int cpt_columns = 0;
    int cpt_lines = starting_line;
    
    while (cpt_columns < _num_of_elements) {
        for (auto it = all_integers[cpt_lines].begin(); it != all_integers[cpt_lines].end(); it++) {
            costs.push_back(*it);
            cpt_columns++;
        }
        
        cpt_lines++;
    }
    
    return cpt_lines;
}

int Problem::readCovers(std::vector<std::vector<int> > all_integers, std::vector<int> &cover, int starting_line) {
    int cpt_lines = starting_line;
    int cpt_rows = 0;
    
    int num_of_covered_row = all_integers[cpt_lines][0];
    cpt_lines++;
    
    while (cpt_rows < num_of_covered_row) {
        for (auto it = all_integers[cpt_lines].begin(); it != all_integers[cpt_lines].end(); it++) {
            cover.push_back(*it);
            cpt_rows++;
        }
        
        cpt_lines++;
    }
    
    return cpt_lines;
}
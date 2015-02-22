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

Instance* InputChecker::readInstance(std::string instance_name) {
    
    std::cout << instance_name << std::endl;
    std::ifstream file(instance_name);
    
    std::vector<int> costs;
    std::vector<std::vector<int>> covers;
    
    if (file.is_open()) {
        std::string line;
        std::vector< std::vector<int> > all_integers;
        
        while ( getline(file, line ) ) {
            std::istringstream is( line );
            all_integers.push_back(
                std::vector<int>(std::istream_iterator<int>(is),
                                 std::istream_iterator<int>() ) );
        }
        
        int last_line_parsed = 0;
        
        int num_of_rows = all_integers[0][0];
        int num_of_columns = all_integers[0][1];

        covers.resize(num_of_rows);
        
        last_line_parsed++;
        
        last_line_parsed = readCosts(all_integers, costs, num_of_columns, last_line_parsed);
        
        for (int i = 0; i < num_of_rows; i++) {
            last_line_parsed = readCovers(all_integers, covers[i], last_line_parsed);
        }
        
        file.close();
    }
    else {
        std::cout << "pas correct" << std::endl;
    }
    
    return new Instance(instance_name, costs, covers);
}

int InputChecker::readCosts(std::vector< std::vector<int> > all_integers, std::vector<int>& costs, int num_of_columns, int starting_line) {
    int cpt_columns = 0;
    int cpt_lines = starting_line;
    
    while (cpt_columns < num_of_columns) {
        for (auto it = all_integers[cpt_lines].begin(); it != all_integers[cpt_lines].end(); it++) {
            costs.push_back(*it);
            cpt_columns++;
        }
        
        cpt_lines++;
    }
    
    return cpt_lines;
}

int InputChecker::readCovers(std::vector<std::vector<int> > all_integers, std::vector<int> &cover, int starting_line) {
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
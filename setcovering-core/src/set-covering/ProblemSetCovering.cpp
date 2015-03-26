#include "ProblemSetCovering.h"

ProblemSetCovering::ProblemSetCovering(std::string file_name, int num_of_elements, int num_of_covers, std::vector<int> costs, std::vector<std::vector<bool>> covers):
Problem(file_name),
_num_of_elements(num_of_elements),
_num_of_subsets(num_of_covers),
_costs(costs),
_covers_by_elements(covers){}

ProblemSetCovering::ProblemSetCovering(std::string file_name):
Problem(file_name) {
    readInstance();
}

ProblemSetCovering::~ProblemSetCovering() {
    _costs.clear();
    
    for (auto it = _covers_by_elements.begin(); it != _covers_by_elements.end(); it++) {
        (*it).clear();
    }
    
    _covers_by_elements.clear();
}

void ProblemSetCovering::readInstance() {
    
    std::ifstream file;
    file.exceptions(std::ifstream::failbit);
    
    std::vector<std::vector<int>> covers;
    
    std::string line;
    std::vector< std::vector<int> > all_integers;
    
    try {
        file.open(_name);
        
        while ( getline(file, line ) ) {
            std::istringstream is( line );
            all_integers.push_back(
                                   std::vector<int>(std::istream_iterator<int>(is),
                                                    std::istream_iterator<int>() ) );
        }
    }
    catch (std::ifstream::failure e) {
        std::cerr << _name << " path is invalid!" << std::endl;
        throw std::ifstream::failure("parser failure");
    }
    
    file.close();
    
    int last_line_parsed = 0;
    
    _num_of_elements = all_integers[0][0];
    _num_of_subsets = all_integers[0][1];
    
    covers.resize(_num_of_elements);
    
    last_line_parsed++;
    
    last_line_parsed = readCosts(all_integers, last_line_parsed);
    
    for (int i = 0; i < _num_of_elements; i++) {
        last_line_parsed = readCovers(all_integers, covers[i], last_line_parsed);
    }
    
    setProblemMatrix(covers);
}

void ProblemSetCovering::setProblemMatrix(const std::vector<std::vector<int> > covers) {
    _covers_by_elements.resize(_num_of_elements);
    
    std::vector<int>::const_iterator it_covers_end;
    std::vector<int>::const_iterator it_covers_begin;
    
    for (int i = 0; i < _num_of_elements; i++) {
        _covers_by_elements[i].resize(_num_of_subsets);
        
        for (int j = 0; j < _num_of_subsets; j++) {
            
            it_covers_begin = covers[i].begin();
            it_covers_end = covers[i].end();
            
            std::vector<int>::const_iterator seacher = std::find(it_covers_begin, it_covers_end, j);
            
            if (seacher != it_covers_end) {
                _covers_by_elements[i][j] = true;
            }
            else {
                _covers_by_elements[i][j] = false;
            }
        }
    }
}

int ProblemSetCovering::readCosts(std::vector< std::vector<int> > all_integers, int starting_line) {
    int cpt_columns = 0;
    int cpt_lines = starting_line;
    
    while (cpt_columns < _num_of_subsets) {
        for (auto it = all_integers[cpt_lines].begin(); it != all_integers[cpt_lines].end(); it++) {
            _costs.push_back(*it);
            cpt_columns++;
        }
        
        cpt_lines++;
    }
    
    return cpt_lines;
}

int ProblemSetCovering::readCovers(std::vector<std::vector<int> > all_integers, std::vector<int> &cover, int starting_line) {
    int cpt_lines = starting_line;
    int cpt_rows = 0;
    
    int num_of_covering_columns = all_integers[cpt_lines][0];
    cpt_lines++;
    
    while (cpt_rows < num_of_covering_columns) {
        for (auto it = all_integers[cpt_lines].begin(); it != all_integers[cpt_lines].end(); it++) {
            cover.push_back(*it);
            cpt_rows++;
        }
        
        cpt_lines++;
    }
    
    return cpt_lines;
}

const std::vector<bool> ProblemSetCovering::getSubset(int subset_index) const {
    std::vector<bool> subset;
    subset.resize(_num_of_elements);
    
    for (int i = 0; i < _num_of_elements; i++) {
        subset[i] = _covers_by_elements[i][subset_index];
    }
    
    return subset;
}

const int ProblemSetCovering::getBestCoveredSubset(const int& subset_index) const {
    std::vector<bool> subset_to_change = getSubset(subset_index);
    int best_candidate = subset_index;
    
    for (int j = 0; j < _num_of_subsets; j++) {
        
        std::vector<bool> candidate_subset = getSubset(j);
        bool isCovered = true;
        int i = 0;
        
        if (j != subset_index) {
            
            while (i < _num_of_elements && isCovered) {
                if (subset_to_change[i] && candidate_subset[i]) {
                    i++;
                }
                else {
                    isCovered = false;
                }
            }
            
            if (i == _num_of_elements && getCost(j) < getCost(subset_index)) {
                best_candidate = j;
            }
        }
    }
    
    return best_candidate;
}

std::ostream& operator << (std::ostream& output, const ProblemSetCovering& pb) {
    output << "SET-COVERING PROBLEM" << std::endl;
    output << "instance name: " << pb._name << std::endl;
    output << "number of elements: " << pb._num_of_elements << std::endl;
    output << "number of sets: " << pb._num_of_subsets << std::endl;
    
    return output;
}
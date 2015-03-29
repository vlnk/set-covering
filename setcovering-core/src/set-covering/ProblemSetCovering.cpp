#include "ProblemSetCovering.h"

ProblemSetCovering::ProblemSetCovering(std::string file_name, int num_of_elements, int num_of_covers, std::vector<int> costs, std::vector<std::vector<bool>> covers):
Problem(file_name),
_num_of_elements(num_of_elements),
_num_of_subsets(num_of_covers),
_costs(costs),
_covers_by_elements(covers){

}

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
            
            std::vector<int>::const_iterator seacher = std::find(it_covers_begin, it_covers_end, j + 1);
            
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

const int ProblemSetCovering::getSmallerCoveredSubset(const int& element_index) const {
    int best_cost = std::numeric_limits<int>::infinity();
    int best_subset = 0;
    
    for (int j = 0; j < _num_of_subsets; j++) {
        
        if (_covers_by_elements[element_index][j]) {
            if (_costs[j] < best_cost) {
                best_cost = _costs[j];
                best_subset = j;
            }
        }
    }
    
    return best_subset;
}

const int ProblemSetCovering::getLargerCoveredSubset(const int& element_index) const {
    int best_cost = 0;
    int best_subset = 0;
    
    for (int j = 0; j < _num_of_subsets; j++) {
        
        if (_covers_by_elements[element_index][j]) {
            if (_costs[j] > best_cost) {
                best_cost = _costs[j];
                best_subset = j;
            }
        }
    }
    
    return best_subset;
}

std::ostream& operator << (std::ostream& output, const ProblemSetCovering& pb) {
    output << "problem: set-covering" << std::endl;
    
    output << static_cast<const Problem&>(pb);
    
    output << "number of elements: " << pb._num_of_elements << std::endl;
    output << "number of sets: " << pb._num_of_subsets << std::endl;
    
    return output;
}
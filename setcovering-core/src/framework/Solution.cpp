#include "Solution.h"

template<typename T>
template<typename U>
Solution<T>::Solution(const Solution<U>& solution):
_objective_function(solution._objective_function) {}

template<typename T>
template<typename U>
Solution<U>& Solution<T>::operator = (const Solution<U>& solution) {
    if (&solution != this) {
        _objective_function = solution._objective_function;
    }
    
    return *this;
}

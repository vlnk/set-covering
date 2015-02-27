cmake_minimum_required(VERSION 2.8.4)
project(setcovering)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    setcovering-core/src/core/Core.cpp
    setcovering-core/src/core/Core.h
    setcovering-core/src/core/InputChecker.cpp
    setcovering-core/src/core/InputChecker.h
    setcovering-core/src/core/Problem.cpp
    setcovering-core/src/core/Problem.h
    setcovering-core/src/metaheuristics/Genetic/AlgorithmGenetic.cpp
    setcovering-core/src/metaheuristics/Genetic/AlgorithmGenetic.h
    setcovering-core/src/metaheuristics/Algorithm.cpp
    setcovering-core/src/metaheuristics/Algorithm.h
    setcovering-core/src/metaheuristics/Solution.cpp
    setcovering-core/src/metaheuristics/Solution.h
    setcovering-core/src/main.cpp)

add_executable(setcovering ${SOURCE_FILES})
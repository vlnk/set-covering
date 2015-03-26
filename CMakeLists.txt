cmake_minimum_required(VERSION 2.8.4)
project(setcovering)

#turn on using solution folders
set_property( GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH setcovering-core//bin/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    setcovering-core/src/core/InputChecker.cpp
    setcovering-core/src/core/InputChecker.h
    setcovering-core/src/framework/Problem.cpp
    setcovering-core/src/framework/Problem.h
    setcovering-core/src/framework/Solution.cpp
    setcovering-core/src/framework/Solution.h
    setcovering-core/src/framework/Algorithm.h
    setcovering-core/src/set-covering/ProblemSetCovering.cpp
    setcovering-core/src/set-covering/ProblemSetCovering.h
    setcovering-core/src/set-covering/random/AlgorithmRandom.cpp
    setcovering-core/src/set-covering/random/AlgorithmRandom.h
    setcovering-core/src/set-covering/random/SimpleSolution.cpp
    setcovering-core/src/set-covering/random/SimpleSolution.h
    setcovering-core/src/main.cpp)

add_executable(setcovering ${SOURCE_FILES})

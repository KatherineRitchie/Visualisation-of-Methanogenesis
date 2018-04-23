cmake_minimum_required(VERSION 3.5)
project(final-project)

set(CMAKE_CXX_STANDARD 14)

add_executable(testing
        src/enzyme.cpp
        src/load.cpp
        src/metabolite.cpp
        src/pathway.cpp
        src/rxn.cpp
        test/HormoneTests.cpp
        )
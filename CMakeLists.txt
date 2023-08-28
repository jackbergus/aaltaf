cmake_minimum_required(VERSION 3.16)
project(ltlsolver)

find_package(BISON)
find_package(FLEX)
add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

BISON_TARGET(MyParser submodules/ltlparser/grammar/ltlparser.y ${CMAKE_CURRENT_SOURCE_DIR}/submodules/ltlparser/ltlparser.c)
FLEX_TARGET(MyScanner submodules/ltlparser/grammar/ltllexer.l ${CMAKE_CURRENT_SOURCE_DIR}/submodules/ltlparser/ltllexer.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(submodules)
include_directories(submodules/minisat/)
include_directories(include)
include_directories(submodules/ltlparser)

bison_target(parser fl.ypp fl.tab.cpp)

add_library(aaltaf OBJECT ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        src/util/utility.cpp
        src/utility.cpp
        src/formula/aalta_formula.cpp
        src/formula/olg_formula.cpp
        src/formula/olg_item.cpp
        submodules/minisat/core/Solver.cc
        src/aaltasolver.cpp
        src/solver.cpp
        src/carsolver.cpp
        submodules/ltlparser/ltl_formula.c
        src/ltlfchecker.cpp
        src/carchecker.cpp
        src/evidence.cpp
        submodules/ltlparser/trans.c)

add_executable(ltlsolver
        main.cpp)

target_link_libraries(ltlsolver z aaltaf)
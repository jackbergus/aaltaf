/* 
 * File:   utility.cpp
 * Author: Jianwen Li
 * Note: An interface for utility functions
 * Created on July 2, 2017
 */
 
 #ifndef UTILITY_H
 #define UTILITY_H
 
 #include "formula/aalta_formula.h"
 #include <vector>
 
 namespace aalta
 {
 	aalta_formula* formula_from (std::vector<aalta_formula*>& ands);
	void print_vec (const std::vector<int>&);
 }

#define AALTAF_TRUE()    (create_operation( eTRUE, nullptr, nullptr ))
#define AALTAF_FALSE()    (create_operation( eFALSE, nullptr, nullptr ))
#define AALTAF_NOT(x)   (create_operation( eNOT, nullptr, ((ltl_formula*)x) ))
#define AALTAF_WNEXT(x)   (create_operation( eWNEXT, nullptr, ((ltl_formula*)x) ))
#define AALTAF_NEXT(x)   (create_operation( eNEXT, nullptr, ((ltl_formula*)x) ))
#define AALTAF_GLOBALLY(x)   (create_operation( eGLOBALLY, nullptr, ((ltl_formula*)x) ))
#define AALTAF_FUTURE(x)   (create_operation( eFUTURE, nullptr, ((ltl_formula*)x) ))
#define AALTAF_UNTIL(x, y)   (create_operation( eUNTIL, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_WUNTIL(x, y)   (create_operation( eWUNTIL, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_RELEASE(x, y)   (create_operation( eRELEASE, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_AND(x, y)   (create_operation( eAND, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_OR(x, y)   (create_operation( eOR, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_IMPLIES(x, y)   (create_operation( eIMPLIES, ((ltl_formula*)x), ((ltl_formula*)y) ))
#define AALTAF_EQUIV(x, y)   (create_operation( eEQUIV, ((ltl_formula*)x), ((ltl_formula*)y) ))


#endif

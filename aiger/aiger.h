 /* 
 * aiger translator to aalta_formula
 * File:   AIGER.h
 * Author: Jianwen Li
 * 
 * Created on November 19, 2014
 */
 
 #ifndef AIGER_H
 #define AIGER_H
 
#define SAFETY true
#define FAIR false

 #include "formula/aalta_formula.h"
 #include <iostream>
 #include <string>
 
 extern "C" {
#include "aiger19.h"
}

aalta_formula* aiger_to_ltl (const std::string&, bool);

aalta_formula* aiger_safety (aiger*);
aalta_formula* aiger_fair (aiger*);

aalta_formula* generate_constraint (aiger*, unsigned);
//aalta_formula* generate_output (aiger*, int);
aalta_formula* generate_bad (aiger*, unsigned);
aalta_formula* generate_fair (aiger*, unsigned);
aalta_formula* generate_justice (aiger*, unsigned);
aalta_formula* generate_formula (aiger*, unsigned);

static std::vector<aalta_formula*> FORMULAS;

#endif


 
 

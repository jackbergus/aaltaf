
#include "formula/aalta_formula.h"
#include "ltlfchecker.h"
#include "carchecker.h"
#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <utility.h>


#define MAXN 100000
char in[MAXN];

using namespace aalta;

void 
print_help ()
{
	cout << "usage: ./aalta_f [-e|-v|-blsc|-t|-h] [\"formula\"]" << endl;
	cout << "\t -e\t:\t print example when result is SAT" << endl;
	cout << "\t -v\t:\t print verbose details" << endl;
	cout << "\t -blsc\t:\t use the BLSC checking method; Default is CDLSC" << endl;
	cout << "\t -t\t:\t print weak until formula" << endl;
	cout << "\t -h\t:\t print help information" << endl;
}

void
ltlf_sat (int argc, char** argv)
{
	bool verbose = true;
	bool evidence = true;
	int input_count = 0;
	bool blsc = false;
	bool print_weak_until_free = false;
	
	for (int i = argc; i > 1; i --)
	{
		if (strcmp (argv[i-1], "-v") == 0)
			verbose = true;
		else if (strcmp (argv[i-1], "-e") == 0)
			evidence = true;
		else if (strcmp (argv[i-1], "-blsc") == 0)
			blsc = true;
		else if (strcmp (argv[i-1], "-t") == 0)
			print_weak_until_free = true;
		else if (strcmp (argv[i-1], "-h") == 0)
		{
			print_help ();
			exit (0);
		}
		else //for input
		{
			if (input_count > 1)
			{
				printf ("Error: read more than one input!\n");
        		exit (0);
			}
			strcpy (in, argv[i-1]);
			input_count ++;
		}
	}
	if (input_count == 0)
	{
		puts ("please input the formula:");
    	if (fgets (in, MAXN, stdin) == NULL)
    	{
        	printf ("Error: read input!\n");
        	exit (0);
      	}
	}


  aalta_formula* af;
  //set tail id to be 1
  af = aalta_formula::TAIL ();  
  af = aalta_formula(in, true).unique();
    af = af->nnf ();
    af = af->add_tail ();
    af = af->remove_wnext ();
    af = af->simplify ();
	/*if (print_weak_until_free)
	{
		cout << af->to_string () << endl;
		return;
	}*/

  af = af->split_next ();
  
  
  
  //LTLfChecker checker (af, verbose);
  // A  t (af, verbose);
  /*
  LTLfChecker *checker;
  if (!blsc)
  	checker = new CARChecker (af, verbose, evidence);
  else
  	checker = new LTLfChecker (af, verbose, evidence);

  bool res = checker->check ();
  printf ("%s\n", res ? "sat" : "unsat");
  if (evidence && res)
  	checker->print_evidence ();
  delete checker;
  */
  if (blsc)
  {
	  LTLfChecker checker (af, verbose, evidence);
	  bool res = checker.check ();
	  printf ("%s\n", res ? "sat" : "unsat");
	  if (evidence && res)
		  checker.print_evidence ();
  }
  else
  {
	CARChecker checker (af, verbose, evidence);
	bool res = checker.check ();
	printf ("%s\n", res ? "sat" : "unsat");
	checker.print_frames();
	if (evidence && res)
		checker.print_evidence ();
  }
  aalta_formula::destroy();
}

#include <chrono>

double check_formula(const std::string& ltlf_string) {
    aalta_formula* af;

    //set tail id to be 1
    af = aalta_formula::TAIL ();
    af = aalta_formula(ltlf_string.c_str(), true).unique();
    //af = af->nnf ();
    af = af->add_tail ();
    af = af->remove_wnext ();
    //af = af->simplify ();
    //af = af->split_next ();
    auto start = std::chrono::system_clock::now();
    CARChecker checker (af, false, true);
    bool res = checker.check ();
    auto end = std::chrono::system_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
    //printf ("%s\n", res ? "sat" : "unsat");
//    return checker.get_inconsistency_measure(res);
}

#include <fstream>
#include <sstream>

int
main (int argc, char** argv){
    std::ifstream t(argv[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::cout << check_formula(buffer.str()) << std::endl;
  return 0;
}

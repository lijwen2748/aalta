#include "Hltlfchecker.h"

using namespace Minisat;

namespace aalta
{
	bool HLTLfChecker::dfs_check (aalta_formula* f){
		if (f->oper () == aalta_formula::True)
			return true;
		if (f->oper () == aalta_formula::False)
			return false;
		visited_.push_back (f);
		if (detect_unsat ())
			return false;
		if (sat_once (f))
		{
			if (verbose_)
				cout << "sat once is true, return from here\n";
			return true;
		}
		else if (f->is_global ())
		{
			visited_.pop_back ();
			push_formula_to_explored (f);
			return false;;
		}
				
		
		//The SAT solver cannot return f as well
		push_formula_to_explored (f);
		
		while (true)
		{
			if (detect_unsat ())
				return false;
			Transition* t = get_one_transition_from (f);
			
			if (t != NULL)
			{
				if (verbose_)
					cout << "getting transition:\n" << t->label ()->to_string() << " -> " << t->next ()->to_string () << endl;
				traces_.push_back (t->label ());
				dfs_level++;
				if (dfs_check (t->next ()))
				{
					delete t;
					return true;
				}
				traces_.pop_back ();
			}
			else //cannot get new states, that means f is not used anymore
			{
				if (verbose_)
					cout << "get a null transition\n";
				visited_.pop_back ();
				push_uc_to_explored ();
				delete t;
				return false;
			}
		}
		visited_.pop_back ();
		dfs_level--;
		return false;
	}
}
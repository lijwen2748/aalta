#include "Hsolver.h"

namespace aalta
{

	HSolver::HSolver (aalta_formula *f, bool verbose, bool partial_on, bool uc_on)
	 {
	 	verbose_ = verbose;
	 	uc_on_ = uc_on;
	 	partial_on_ = partial_on;
	 	unsat_forever_ = false;

	 	max_used_id_ = f->id ();
		tail_ = aalta_formula::TAIL ()->id ();
		build_X_map_priliminary (f);
		//tail_ = ++max_used_id_;
		generate_clauses (f);
		coi_set_up (f);
		if (verbose_)
		{
			cout << "id of input formula is " << f->id () << endl;
			cout << "tail_ is " << tail_ << endl;
			cout << "max_used_id_ is " << max_used_id_ << endl;
		  cout << "//////////////////////////////////////////////////////\n";
			print_formula_map ();			
			cout << "//////////////////////////////////////////////////////\n";
			print_x_map ();
			cout << "//////////////////////////////////////////////////////print coi ////////////////////////\n";
			print_coi ();
			cout << "//////////////////////////////////////////////////////\n";
			print_clauses ();
			cout << "//////////////////////////////////////////////////////\n";
		}
	 }

	bool HSolver::check_tail(aalta_formula* f, int dfs_level){
		assert (!unsat_forever_);
		get_assumption_from (f);
		assumption_.push (SAT_lit (tail_));				// check tail, check formula is the last state
														// uc flags pos 0 should be tail_, we can put Line 8 to uc_flgs
		if (verbose_)
		{
			cout << "check_tail: assumption_ is" << endl;
			for (int i = 0; i < assumption_.size (); i ++)
				cout << lit_id (assumption_[i]) << ", ";
			cout << endl;
		}
		for(int i = 0; i < uc_flags.size(); ++i){  			
			if(i != dfs_level)
				assumption_.push(uc_flags[i]);
			else 
				assumption_.push(~uc_flags[i]);  		// v(uc_flags[dfs_level]) := 0, turn on the reason
		}
		lbool ret = solveLimited (assumption_);
		if (ret == l_True)
     		return true;
   		else if (ret == l_Undef)
     		exit (0);
     	else if (ret == l_False){
     		vector<Lit> reason = get_uc();
     													// assert reason > 0
     													// what about reason length = 1, reason length = 2

     		if(reason.size() > 2){						// why conflict is 0 0
     			newVar();
     			Lit tmp = mkLit(nVars() - 1, true); 		// add a new variable v, and construct a new literal ~v
     			reason.push_back(tmp);
     			uc_flags.push(tmp); 					// add v to uc_flags as the flag of this reason
     		}
     		vec<Lit> tmpVec;
     		for(int i = 0; i < reason.size(); ++i){
     			tmpVec.push(reason[i]);
     		}
     		addClause_(tmpVec); 						// add reason with flag to F, does not change the satisfiability, since v can be assigned to 1.
     	}

   		return false;
	}

	vector<Lit> HSolver::get_uc(){
		vector<Lit> reason;
		for(int i = 0; i < conflict.size(); ++i){
			reason.push_back(~conflict[i]);
		}

		return reason;
	}

}
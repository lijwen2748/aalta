#include "solver.h"
#include <vector>

using namespace Minisat;
using namespace std;

namespace aalta{
	class HSolver : public Solver {
	public:	
		HSolver (aalta_formula *f, bool verbose = false, bool partial_on = false, bool uc_on = true);
		~HSolver () {};		

		vec<Lit> 				uc_flags; 		// v(uc_flags[i]) := 0, at F_i 
		bool check_tail	(aalta_formula* f, int dfs_level); 	// add uc from check_tail to F
		vector<Lit> get_uc (); 					// get uc, return vec<Lit>
		aalta_formula *f;

	};
}
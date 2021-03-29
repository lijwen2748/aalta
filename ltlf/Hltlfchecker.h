#include "ltlfchecker.h"
#include "Hsolver.h"

namespace aalta
{
	class HLTLfChecker : public LTLfChecker
	{
	public : 
		HLTLfChecker (aalta_formula *f, bool verbose = false) {
			to_check_ = f;
			verbose_ = verbose;
			hsolver_ = new HSolver (f, verbose_);}

		bool dfs_check (aalta_formula *f); 		// record current level of the dfs search
		inline bool sat_once (aalta_formula* f)   //check whether the formula can be satisfied in one step (the terminating condition of checking)
		{
			return hsolver_->check_tail (f, dfs_level);
		}

		int dfs_level = 0;
		HSolver *hsolver_;
	};

}
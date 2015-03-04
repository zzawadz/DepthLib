/*
 * local_depths.hpp
 *
 *  Created on: March 04, 2015
 *      Author: zzawadz
 */

#include "../local_depth.hpp"

namespace Depth 
{
    namespace LocalDepthUtils 
    {
      arma::mat symmetrization(arma::rowvec x, const arma::mat& y)
      {
	 x = 2*x; // for symmetrization 
	 arma::mat ySym = y;
	 size_t nrows = y.n_rows;
	 
	 for(size_t i = 0; i < nrows; i++)
	 {
	   ySym.row(i) = x - ySym.row(i);
	 }
	return arma::join_cols(y, ySym);
      }
    }
}

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
      
      arma::mat neighborhood(arma::rowvec x, arma::mat y, const Depth::DepthFunction& depthFnc, double beta)
      {
	arma::mat ySym = symmetrization(x, y);
	arma::vec depths = depthFnc.calculate_depth(y, ySym);
	//std::cout << "Depths inside neigh:" << depths << std::endl;
	y = y.rows(sort_index(depths, "descend"));
	
	size_t endRow = static_cast<size_t>(y.n_rows * (1.0 -beta)) - 1;
	return y.rows(0, endRow);
      }
      
      
    }
}

/*
 * local_depths.hpp
 *
 *  Created on: March 04, 2015
 *      Author: zzawadz
 */

#include "../local_depth.hpp"

namespace Depth 
{
    LocalDepth::LocalDepth(DepthFunction& depthFnc, double beta) : depthFncFirst(&depthFnc), depthFncSecond(&depthFnc), beta(beta) {};
    LocalDepth::LocalDepth(DepthFunction& depthFnc, DepthFunction& depthFncSecond, double beta) : depthFncFirst(&depthFnc), depthFncSecond(&depthFncSecond), beta(beta) {};
    
    arma::vec LocalDepth::calculate_depth(const arma::mat& x, const arma::mat& y) const
    {
      return LocalDepthUtils::local_depth(x, y, *this->depthFncFirst, *this->depthFncSecond, this->beta);
    }
    
    
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
      
      double local_depth_single(const arma::rowvec& x, const arma::mat& y, const Depth::DepthFunction& depthFnc, const Depth::DepthFunction& depthFncSecond, double beta)
      {
	arma::mat yNeigh = neighborhood(x, y, depthFnc, beta);
	return depthFncSecond.calculate_depth(x, yNeigh).at(0);
      }
      
      arma::vec local_depth(const arma::mat& x, const arma::mat& y, const Depth::DepthFunction& depthFnc, const Depth::DepthFunction& depthFncSecond, double beta)
      {
	size_t nElem = x.n_rows;
	arma::vec result(nElem);
	for(size_t i = 0; i < nElem; i++)
	{
	  result(i) = local_depth_single(x.row(i), y, depthFnc, depthFncSecond, beta);
	}
	return result;
      }
      
    }
}

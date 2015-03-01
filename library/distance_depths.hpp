/*
 * euclid_depth.hpp
 *
 *  Created on: Sep 14, 2014
 *      Author: zzawadz
 */

#ifndef DISTANCE_DEPTH_HPP_
#define DISTANCE_DEPTH_HPP_

#include "DepthLib_include.hpp"
#include "depth.hpp"

namespace Depth
{
  class EuclidDepth : public Depth::DepthFunction
    {
      public:
	EuclidDepth();
	EuclidDepth(arma::rowvec center);
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y);
	
	
      private:
	 arma::rowvec center;
	
    };
  
  namespace Euclid
  {
    arma::vec euclid_depth(const arma::mat& x, const arma::rowvec& center);
    arma::vec euclid_depth(const arma::mat& x, const arma::mat& y);
    arma::vec euclid_depth(const arma::mat& x);
  }
  
  
  /////////////////////////// Mahalanobis
  
  
  namespace Mahalanobis
  {
    arma::vec mah_depth(const arma::mat& x);
    arma::vec mah_depth(const arma::mat& x, const arma::rowvec& mean);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& mean);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov, const arma::rowvec& mean);
  }

}


#endif /* DISTANCE_DEPTH_HPP_ */

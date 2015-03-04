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
  
  namespace LP
  {
    arma::vec lp_depth(const arma::mat& x, const arma::mat& y, const double &p, const double& a, const double& b);
  }
  
////////////// Euclid depth
  class EuclidDepth : public Depth::DepthFunction
    {
      public:
	EuclidDepth();
	EuclidDepth(arma::rowvec center);
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) const;
	
	
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
  class MahalanobisDepth : public Depth::DepthFunction
    {
      public:
	MahalanobisDepth();
	MahalanobisDepth(arma::mat cov);
	MahalanobisDepth(arma::rowvec center);
	MahalanobisDepth(arma::rowvec center, arma::mat cov);
	
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) const;
	
	
      private:
	 arma::rowvec center;
	 arma::mat    cov;
	
    };
  
  namespace Mahalanobis
  {
    arma::vec mah_depth(const arma::mat& x);
    arma::vec mah_depth(const arma::mat& x, const arma::rowvec& center);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& center);
    arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& center, const arma::mat& cov);
     
  }

}


#endif /* DISTANCE_DEPTH_HPP_ */

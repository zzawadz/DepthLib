/*
 * euclid_depth.hpp
 *
 *  Created on: Sep 14, 2014
 *      Author: zzawadz
 */

#ifndef EUCLID_DEPTH_HPP_
#define EUCLID_DEPTH_HPP_

#include "DepthLib_include.hpp"
#include "depth.hpp"

namespace Depth
{
  
  namespace Euclid
  {
    
    class EuclidDepth : public Depth::DepthFunction
    {
      public:
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y);
    };
    
    
    arma::vec euclid_depth(const arma::mat& x, const arma::rowvec& center);
    arma::vec euclid_depth(const arma::mat& x, const arma::mat& y);
    arma::vec euclid_depth(const arma::mat& x);
  }

}


#endif /* EUCLID_DEPTH_HPP_ */

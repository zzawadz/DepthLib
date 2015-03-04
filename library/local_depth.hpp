/*
 * standard_depths.hpp
 *
 *  Created on: March 04, 2015
 *      Author: zzawadz
 */

#ifndef LOCAL_DEPTH_HPP_
#define LOCAL_DEPTH_HPP_

#include "depth.hpp"
#include "DepthLib_include.hpp"

namespace Depth
{

  class LocalDepth : public Depth::DepthFunction
  {
      public:
	LocalDepth(DepthFunction& depthFnc);
	LocalDepth(DepthFunction& depthFnc, DepthFunction& depthFncSecond);
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) const;
	
      private:
	const DepthFunction* depthFncFirst; 
	const DepthFunction* depthFncSecond;
  };
  

  
}

#endif /* STANDARD_DEPTH_HPP_ */
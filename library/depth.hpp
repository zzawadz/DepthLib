/*
 * depth.hpp
 *
 *  Created on: Sep 14, 2014
 *      Author: zzawadz
 */

#ifndef DEPTH_HPP_
#define DEPTH_HPP_

#include <functional>
#include <memory>
#include "DepthLib_include.hpp"

namespace Depth
{

  class DepthFunction
  {
      public:
	virtual arma::vec calculate_depth(const arma::mat& x, const arma::mat& y) =0;
  };
  
  arma::vec depth(const arma::mat& x, const arma::mat& y, DepthFunction& depthFnc); //, const std::function<arma::vec(const arma::mat&, const arma::mat&)> depFnc);

  
  
}


#endif /* DEPTH_HPP_ */
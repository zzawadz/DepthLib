/*
 * depth.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: zzawadz
 */

#include "../depth.hpp"

namespace Depth {

arma::vec depth(const arma::mat& x, const arma::mat& y, DepthFunction& depthFnc) //const std::function<arma::vec(const arma::mat&, const arma::mat&)> depFnc)
{
  return depthFnc.calculate_depth(x, y);
}

}
/*
 * standard_depths.hpp
 *
 *  Created on: Sep 12, 2014
 *      Author: zzawadz
 */

#ifndef STANDARD_DEPTHS_HPP_
#define STANDARD_DEPTHS_HPP_

#include "depth.hpp"
#include "DepthLib_include.hpp"

namespace Depth
{
// Tukey's depth
namespace TukeyUtils
{
  arma::vec tukey_depth1d(const arma::colvec& x, arma::colvec y);
  
  double get_depths1(double m,const double j);
  double get_HDEP(size_t NT, size_t N, double NUMH);
  arma::vec get_ALPHA(const arma::vec& X, const arma::vec& Y,const double& U,const double& V, const double& P, const double& P2,const double& EPS);
  double tukey_depth2d_exact(double U, double V,const arma::mat& m);  
}
  
}

#endif /* STANDARD_DEPTHS_HPP_ */
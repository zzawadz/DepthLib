/*
 * euclid_depth.hpp
 *
 *  Created on: Sep 17, 2014
 *      Author: zzawadz
 */

#ifndef MAH_DEPTH_HPP_
#define MAH_DEPTH_HPP_

#include "DepthLib_include.hpp"

namespace depth
{

  arma::vec mah_depth(const arma::mat& x);
  arma::vec mah_depth(const arma::mat& x, const arma::rowvec& mean);
  arma::vec mah_depth(const arma::mat& x, const arma::mat& y);
  arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov);
  arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::rowvec& mean);
  arma::vec mah_depth(const arma::mat& x, const arma::mat& y, const arma::mat& cov, const arma::rowvec& mean);


}


#endif /* MAH_DEPTH_HPP_ */
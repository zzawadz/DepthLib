/*
 * modified_band_depth.hpp
 *
 *  Created on: Sep 12, 2014
 *      Author: zzawadz
 */

#ifndef MB_DEPTH_HPP_
#define MB_DEPTH_HPP_

#include "DepthLib_include.hpp"


namespace FncDepth
{

arma::vec mb_depth(const arma::mat& x);
arma::vec mb_depth(const arma::mat& x, const arma::mat& y);

}


 /// Utils functions for MBDepth
namespace MBD
{
	double choose(double n, double k);
	arma::vec mbd_col(arma::vec x);
	arma::vec mbd_col_ref(arma::vec x,arma::vec y);
}


#endif /* MODIFIED_BAND_DEPTH_HPP_ */

/*
 * euclid_depth.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: zzawadz
 */

#include "../euclid_depth.hpp"

namespace depth
{

arma::vec euclid_depth(arma::mat x, arma::rowvec center)
{
	arma::vec depth(x.n_rows);

	x = x-arma::repmat(center, x.n_rows, 1);
	x = x % x;
	x = sum(x,1);
	x = sqrt(x);
	depth = 1/(x+1);

	return depth;
}

arma::vec euclid_depth(const arma::mat& x)
{
	arma::rowvec center = arma::mean(x, 0);
	return euclid_depth(x, center);
}

arma::vec euclid_depth(const arma::mat& x, const arma::mat& y)
{
	arma::rowvec center = arma::mean(y, 0);
	return euclid_depth(x, center);
}


}

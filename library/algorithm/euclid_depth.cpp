/*
 * euclid_depth.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: zzawadz
 */

#include "../euclid_depth.hpp"

namespace depth
{

arma::vec euclid_depth(const arma::mat& x, const arma::rowvec& center)
{
	arma::vec depth(x.n_rows);
	
	/*arma::mat tx = x;
	tx = tx-arma::repmat(center, x.n_rows, 1);
	tx = tx % tx;
	tx = sum(tx,1);
	tx = sqrt(tx);*/
	
	size_t n = x.n_rows;
	arma::rowvec tmp;
	
	for(size_t i = 0; i < n; i++)
	{
	  tmp = x.row(i) - center;
	  depth(i) = sqrt(sum(tmp % tmp));
	}
	
	depth = 1/(depth + 1);

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

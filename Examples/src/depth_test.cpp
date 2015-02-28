/*
 * depth_test.cpp
 *
 *  Created on: Sep 14, 2014
 *      Author: zzawadz
 */


#include <iostream>
#include "DepthLib.hpp"
#include "../Utils/Utils.hpp"

int main()
{
	arma::mat x(10,2);
	x.randn();	
	/*arma::rowvec cntr; cntr.zeros(2);
	
	const std::function<arma::vec(const arma::mat&, const arma::mat&)> eucDepth = Depth::euclid_depth;
	std::cout << Depth::depth(x,cntr,eucDepth);*/
	
	return 0;
}

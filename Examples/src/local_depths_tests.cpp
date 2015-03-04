/*
 * standard_depths_test.cpp
 *
 *  Created on: March 2, 2015
 *      Author: zzawadz
 */


#include <iostream>
#include "DepthLib.hpp"
#include "../Utils/Utils.hpp"

int main()
{	
	arma::colvec x = arma::linspace(1.0, 10.0,10);
	arma::rowvec u = {10.0, 100.0};
	arma::mat xmat(10,2);
	xmat.col(0) = x; xmat.col(1) = x;
	std::cout << Depth::LocalDepthUtils::symmetrization(u, xmat) << std::endl;
	
	//arma::mat big(1e6,2);
	//big.randn();
	//std::cout << "Symmetrization took " 
	//<< measure<>::execution( [&]() { Depth::LocalDepthUtils::symmetrization(u, big); }) << " microseconds. "  << std::endl;

	
	return 0;
}
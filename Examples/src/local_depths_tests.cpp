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
	
	
	Depth::EuclidDepth euclidDepth;
	std::cout << "Neighbourhood: " << Depth::LocalDepthUtils::neighborhood(u, xmat, euclidDepth, 0.5) << std::endl;
	std::cout << "Local depth: " << Depth::LocalDepthUtils::local_depth(xmat, xmat, euclidDepth, euclidDepth, 0.5) << std::endl;
	
	
	//arma::mat big(1e4,2);
	//big.randn();
	//std::cout << "Local depth took " 
	//<< measure<>::execution( [&]() { Depth::LocalDepthUtils::local_depth(big, big, euclidDepth, euclidDepth, 0.5); }) << " microseconds. "  << std::endl;
	// aprox 63s...
	
	return 0;
}
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
	arma::colvec y = arma::linspace(1.0, 10.0,10);
	
	std::cout << Depth::TukeyUtils::tukey_depth1d(x,y) << std::endl;
	
	//arma::colvec big(10000000);
	//big.randn();
	
	//std::cout << "Depth calculation for vector of size 1000000 took " 
	//<< measure<>::execution( [&]() { Depth::TukeyUtils::tukey_depth1d(big, big); }) << " microseconds. "  << std::endl;

	
	return 0;
}
/*
 * euclid_test.cpp
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
	arma::rowvec cntr; cntr.zeros(2);
	
	
	std::cout << "euclid_depth with center: " << std::endl 
	<< depth::euclid_depth(x, cntr);
	
	std::cout << "euclid_depth: " << std::endl
	<< depth::euclid_depth(x);
	std::cout << "euclid_depth with reference set: " << std::endl
	<< depth::euclid_depth(x, x);
	
	arma::mat big(1000000, 1000);
	big.randn();
	
	std::cout << "Depth calculation for matrix of size 1000000x1000 took " 
	<< measure<>::execution( [&]() { depth::euclid_depth(big); }) << " microseconds. "  << std::endl;
	
	return 0;
}

/*
 * functional_depths_test.cpp
 *
 *  Created on: March 2, 2015
 *      Author: zzawadz
 */


#include <iostream>
#include "DepthLib.hpp"
#include "../Utils/Utils.hpp"

int main()
{
	arma::mat x(10,20);
	x.randn();
	Depth::EuclidDepth eucildDepth;
	Depth::FraimanMunizDepth fmDepth(eucildDepth);
	
	std::cout << "Test FM Depth" << std::endl;
	std::cout << "FMDepth: " << fmDepth.calculate_depth(x,x) << std::endl;

	
	return 0;
}

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
	Depth::EuclidDepth euclidDepth;
	Depth::EuclidDepth euclidDepth2(cntr);
	
	std::cout << euclidDepth.calculate_depth(x,x) << std::endl << std::endl;
	std::cout << Depth::depth(x,x,euclidDepth) << std::endl;
	std::cout << Depth::depth(x,x,euclidDepth2);
	/*
	
	
	Depth::euclid_depth(x, cntr);
	std::cout << "euclid_depth with center: ok!\n";
	*/
	/*
	Depth::euclid_depth(x);
	std::cout << "euclid_depth: - ok!\n";
	Depth::euclid_depth2(x, x);
	std::cout << "euclid_depth with reference set: - ok!\n";*/
	
	//arma::mat big(100, 10);
	//big.randn();
	//std::cout << "Depth calculation for matrix of size 100000x1000 took " 
	//<< measure<>::execution( [&]() { depth::euclid_depth(big); }) << " microseconds. "  << std::endl;
	
	return 0;
}

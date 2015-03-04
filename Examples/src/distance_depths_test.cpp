/*
 * distance_depths_test.cpp
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
	Depth::EuclidDepth euclidDepthCntr(cntr);
	
	std::cout << "Euclid: "    << std::endl;
	std::cout << "Standard:"   << euclidDepth.calculate_depth(x,x) << std::endl << std::endl;
	std::cout << "Standard2: " << Depth::depth(x,x,euclidDepth) << std::endl;
	std::cout << "Center: "    << Depth::depth(x,x,euclidDepthCntr) << std::endl;
	
	
	/// Values:
	arma::colvec xx = arma::linspace(1.0, 10.0,10);
	arma::mat xmat(10,2);
	xmat.col(0) = xx; xmat.col(1) = xx;
	std::cout << "Depth Euclid values:" << std::endl;
	std::cout << euclidDepth.calculate_depth(xmat, xmat) << std::endl;
	
	//// Mahalanobis
	arma::mat cov = arma::cov(x);
	Depth::MahalanobisDepth mahDeph;
	Depth::MahalanobisDepth mahDephCov(cov);
	Depth::MahalanobisDepth mahDephCenter(cntr);
	Depth::MahalanobisDepth mahDephCenterCov(cntr, cov);
	
	std::cout << "Mahalanobis: " << std::endl;
	std::cout << "Standard: "  << Depth::depth(x,x,mahDeph) << std::endl;
	std::cout << "Cov: "       << Depth::depth(x,x,mahDephCov) << std::endl;
	std::cout << "Center: "    << Depth::depth(x,x,mahDephCenter) << std::endl;
	std::cout << "CenterCov: " << Depth::depth(x,x,mahDephCenterCov) << std::endl;
	
	return 0;
}

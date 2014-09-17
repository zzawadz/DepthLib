#include <iostream>
#include "DepthLib.hpp"
#include "../Utils/Utils.hpp"

int main()
{
	arma::mat x(10,2);
	x.randn();
	arma::rowvec cntr; cntr.zeros(2);
	
	
	std::cout << "mah_depth with center: " << std::endl 
	<< depth::mah_depth(x, cntr);
	
	std::cout << "mah_depth: " << std::endl
	<< depth::mah_depth(x);
	std::cout << "mah_depth with reference set: " << std::endl
	<< depth::mah_depth(x, x);
	
	arma::mat big(100000, 1000);
	big.randn();
	
	std::cout << "Depth calculation for matrix of size 100000x1000 took " 
	<< measure<>::execution( [&]() { depth::mah_depth(big); }) << " microseconds. "  << std::endl;
	
	return 0;
}
//============================================================================
// Name        : Examples.cpp
// Author      : Zygmunt Zawadzki
// Version     :
// Copyright   : MIT
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DepthLib.hpp"
#include "../headers/euclid_test.hpp"
#include <chrono>





int main() {


	euclid_test();
	/*arma:: mat x(100,5);
	x.randn();
	arma::vec d1 = depth::mb_depth(x);
	arma::vec d2 = depth::mb_depth(x,x);

	size_t nrep = 100;
	arma::vec time(nrep);
	arma::vec time2(nrep);

	for(size_t i = 0; i < nrep; i++)
	{
		time[i]  = measure<>::execution( [&]() { depth::mb_depth(x); });
		time2[i] = measure<>::execution( [&]() { depth::mb_depth(x, x); });
	}

	std:: cout << "Mean time for standard algorithm: " << arma::mean(time2 ) << std::endl
			<< "Mean time for new alogrithm: " << arma::mean(time) << std::endl;*/

	return 0;
}

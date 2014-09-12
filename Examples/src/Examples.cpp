//============================================================================
// Name        : Examples.cpp
// Author      : Zygmunt Zawadzki
// Version     :
// Copyright   : MIT
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DepthLib.hpp"
#include <chrono>

template<typename TimeT = std::chrono::microseconds>
struct measure
{
    template<typename F>
    static typename TimeT::rep execution(F const &func)
    {
        auto start = std::chrono::system_clock::now();
        func();
        auto duration = std::chrono::duration_cast< TimeT>(
            std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

int main() {

	arma:: mat x(1000,50);
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
			<< "Mean time for new alogrithm: " << arma::mean(time) << std::endl;

	return 0;
}

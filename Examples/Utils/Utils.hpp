#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <chrono>

// adopted from http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time - Nikos Athanasiou
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

#endif /* UTILS_HPP_ */
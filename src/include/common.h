#pragma once

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
namespace vin {

    template<typename T>
    std::vector<T> slice(std::vector<T> const &v, int m, int n)
    {
        auto first = v.cbegin() + m;
        auto last = v.cbegin() + n + 1;
    
        std::vector<T> vec(first, last);
        return vec;
    }

       

}
int test( std::string, std::string, std::string );

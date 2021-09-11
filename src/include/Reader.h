#pragma once

#include "common.h"
class Reader {
    public:
        Reader();
        ~Reader();
        static cv::Mat read(std::string, float);
        static void resize(cv::Mat&, float);
    private: 
        
};
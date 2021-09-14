


#pragma once

#include "common.h"
#include "Extractor.h"

class Matcher {
    public:
        Matcher();
        ~Matcher();
        enum Type{
            Flann,
            BruteForce,
            BruteForceSq
        };
        // helper function that calls constructer of the matcher Type
        std::vector<cv::DMatch> calculate(Extractor, Extractor, Type);
        float getScore();

    private : 
        template<typename T>
        std::vector<cv::DMatch> calculate(Extractor, Extractor, T, const float);
        std::vector<cv::DMatch> filter(std::vector<cv::DMatch>, Extractor, Extractor);
        float _homographyMatchesRatio, _goodMatchesRatio;
};
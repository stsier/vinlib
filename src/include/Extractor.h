
#pragma once

#include "common.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>

#define LOG(severity) COMPACT_GOOGLE_LOG_ ## severity.stream()


class Extractor {
    public:
        Extractor();
        ~Extractor();
        void calcuateSift(cv::Mat&, int = 0); 
        std::vector<cv::KeyPoint> getKeyPoints(); 
        cv::Mat getDescriptors(); 

    private:
        cv::Ptr<cv::SiftFeatureDetector> _featureDetector;
        cv::Ptr<cv::SiftDescriptorExtractor> _featureExtractor;
        std::vector<cv::KeyPoint> _keypoints;
        cv::Mat _descriptors;
};
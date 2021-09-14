#pragma once
       
#include "common.h"

//  Haar Feature-based Cascade Classifier for Object Detection
#include <opencv2/objdetect.hpp> 

class Detector {
    public:
        Detector(std::string);
        ~Detector();
        std::vector<cv::Rect> process(cv::Mat& , double);
        
    private:
        cv::CascadeClassifier _cascade;
        void load(std::string); 
};
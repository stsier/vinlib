
#pragma once

#include "common.h"

class Drawer {
    public:
        Drawer();
        ~Drawer();
      /*  void draw(cv::Mat&, const std::vector<cv::Rect>&, double); 
        void draw(cv::Mat&, std::vector<cv::KeyPoint>); */
        void draw(cv::Mat&, cv::Mat&, const std::vector<cv::KeyPoint>&, const std::vector<cv::KeyPoint>&, const std::vector<cv::DMatch>&, cv::Mat&);
        void show(std::string, cv::Mat&); 
};
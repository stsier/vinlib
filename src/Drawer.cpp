#include "include/Drawer.h"

#include <opencv2/features2d.hpp>

using namespace std; 

Drawer::Drawer() {

}

Drawer::~Drawer() {

}

void Drawer::draw(cv::Mat& img1, cv::Mat& img2, const std::vector<cv::KeyPoint>& keyPoints1, const  std::vector<cv::KeyPoint>& keyPoints2, const  std::vector<cv::DMatch>& matches, cv::Mat& imgOut) {
    cv::drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgOut, cv::Scalar::all(-1), cv::Scalar::all(-1),std::vector< char >(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS  );
}

void Drawer::show(string header, cv::Mat& img) {
   // cv::imshow(header, img); needs highgui enabled
}
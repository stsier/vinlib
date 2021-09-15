#include "include/Reader.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std; 

Reader::Reader() {

}

Reader::~Reader() {

}

cv::Mat Reader::read(string fileName, float size) {

    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
    if (!image.data)
    {
        cout << "File " 
             << (fileName) 
             << " not found" 
             << endl;
        throw "File not found";
    } else if (image.empty())
    {
        cout << "File " 
             << (fileName) 
             << " is not an image file" 
             << endl;
        throw "File an imge file";
    }
     
    resize(image, size); 
    return image;
}

void Reader::resize(cv::Mat& img, float size) {
    cv::resize(img, img, cv::Size(), size, size, cv::INTER_LINEAR); 
}
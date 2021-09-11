#include "include/Reader.h"

#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>  

using namespace std; 

Reader::Reader() {

}

Reader::~Reader() {

}

cv::Mat Reader::read(string fileName, float size) {
   // LOG(INFO) << "[Extract Feature] Compute SIFT features using opencv sift\n";
    
   /* cout << "Detection des visages\nveillez entrer le chemin d'accès :" << endl;
    cin >> filePath ;
    cout << "veillez entrer le nom du fichier :" << endl;
    cin >> fileName;*/
    // load the image in BGR format
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
    cv::resize(img, img, cv::Size(), size, size, cv::INTER_LINEAR_EXACT); 
}
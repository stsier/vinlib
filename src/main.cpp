
#include "common.h"
#include <opencv2/highgui.hpp>  
#include <iostream>


#include "include/Reader.h"
//#include "include/Detector.h"
#include "include/Drawer.h"
#include "include/Extractor.h"
#include "include/Matcher.h"

using namespace std; 


/* prototype de la fonction qui détecte les visages et qui dessine ensuite les cercles 
*  [0] Mat& - matrice des pixels pour image 2D
*  [1] CascadeClassifier& - classificateur cascade
*  [2] double - facteur de mise à l'échelle 
*/

int main()
{
  //  cout << "ENV is " << std::getenv("HOME") << endl;
    string filePath = "/mnt/d/Nextcloud Sergei/Vintuoso";
    string fileName = "cc.jpg";
    

    try {
        string fullPath = filePath + "/" + fileName;
      /*  Detector faceDetector("/home/sergei/opencv-master/data/lbpcascades/lbpcascade_frontalface_improved.xml");
        double scale = 1.3;
        cv::Mat img = Reader::read(fullPath);
        
        Drawer drawFaces;
        vector<cv::Rect> faces = faceDetector.process(img, scale);
        drawFaces.draw(img, faces, scale);
        drawFaces.show(img);*/

        cv::Mat img1 = Reader::read(filePath+"/IMG_3788.jpg", 1);
        cv::Mat img2 = Reader::read(filePath+"/IMG_3765.jpg", 1);

        Extractor extractor1, extractor2;
        extractor1.calcuateSift(img1,0);
        extractor2.calcuateSift(img2,0);


        Matcher matcher;
        cv::Mat imgOut;

        vector<cv::DMatch> matches1 = matcher.calculate(extractor1, extractor2, Matcher::Flann);
        cout << "------------------------ Flann matcher : " << 100 * matcher.getScore() << "%" << endl;
        vector<cv::DMatch> matches2 = matcher.calculate(extractor1, extractor2, Matcher::BruteForce);
        cout << "------------------------ BruteForce matcher : " << 100 * matcher.getScore() << "%" << endl;
        vector<cv::DMatch> matches3 = matcher.calculate(extractor1, extractor2, Matcher::BruteForceSq);
        cout << "------------------------ BruteForceSq matcher : " << 100 * matcher.getScore() << "%" << endl;

      
        Drawer drawSift;
        drawSift.draw(img1, img2, extractor1.getKeyPoints(),extractor2.getKeyPoints(), matches1, imgOut);
        Reader::resize(imgOut, 0.5);
      //  drawSift.show("Mather 1", imgOut);cv::waitKey(0);

        drawSift.draw(img1, img2, extractor1.getKeyPoints(),extractor2.getKeyPoints(), matches2, imgOut);
        Reader::resize(imgOut, 0.5);
        drawSift.show("Mather 2", imgOut);cv::waitKey(0);
       

        drawSift.draw(img1, img2, extractor1.getKeyPoints(),extractor2.getKeyPoints(), matches3, imgOut);
        Reader::resize(imgOut, 0.5);
        //drawSift.show("Mather 3", imgOut); cv::waitKey(0); 
        

    } 
    catch(exception e) {
        cout << "error\n";
    }

   
    return 0;
}


 
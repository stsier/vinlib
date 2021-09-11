#include "include/Drawer.h"

#include <opencv2/highgui.hpp>   
#include <opencv2/imgproc.hpp>   
#include <opencv2/features2d.hpp>

//#include <vector>
using namespace std; 

Drawer::Drawer() {

}

Drawer::~Drawer() {

}
/*
void Drawer::draw(cv::Mat& img, const vector<cv::Rect>& objects, double scale) {
   // LOG(INFO) << "[Extract Feature] Compute SIFT features using opencv sift\n";

    // parcour du vector des visages détectés
    for (size_t i = 0; i < objects.size(); i++)
    {
        cv::Rect r = objects[i];
        cv::Point center;
        // la couleur du cercle
        cv::Scalar color = cv::Scalar(0, 255, 0); 
        int radius;
        // calcul de la position du centre du cercle et de son rayon
        // cvRound pour arrondir les valeurs à point flottant 
        center.x = cv::cvRound((r.x + r.width * 0.5) * scale);
        center.y = cv::cvRound((r.y + r.height * 0.5) * scale);
        radius = cv::cvRound((r.width + r.height) * 0.25 * scale);
        // dessiner le cercle sur l'image originale
        cv::circle(img, center, radius, color, 2, 8, 0);
    }

}


void Drawer::draw(Mat& img, vector<cv::KeyPoint> keyPoints) {

    cv::drawKeypoints(img, keyPoints, img);

}
*/

void Drawer::draw(cv::Mat& img1, cv::Mat& img2, const std::vector<cv::KeyPoint>& keyPoints1, const  std::vector<cv::KeyPoint>& keyPoints2, const  std::vector<cv::DMatch>& matches, cv::Mat& imgOut) {
    cv::drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgOut, cv::Scalar::all(-1), cv::Scalar::all(-1),std::vector< char >(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS  );
}

void Drawer::show(string header, cv::Mat& img) {

    cv::imshow(header, img);
}
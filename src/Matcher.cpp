
#include "include/Matcher.h"
#include <opencv2/features2d.hpp>
#include <iostream>
//#include "opencv2/xfeatures2d.hpp"
#include "opencv2/calib3d.hpp"
#include <iomanip>
using namespace std;

Matcher::Matcher() {

}
Matcher::~Matcher() {

}
vector<cv::DMatch> Matcher::calculate(Extractor extractor1, Extractor extractor2, Type type) {
    if(type == Flann) {
        cv::FlannBasedMatcher matcher; 
        return calculate<cv::FlannBasedMatcher>(extractor1, extractor2, matcher,  0.7f);
    }
    else if(type == BruteForce)  {
        cv::BFMatcher matcher (cv::NORM_L2);
        return calculate<cv::BFMatcher>(extractor1, extractor2, matcher,  0.7f);
    }
    else if(type == BruteForceSq)  {
        cv::BFMatcher matcher (cv::NORM_L2SQR);
        return calculate<cv::BFMatcher>(extractor1, extractor2, matcher,  0.5f);
    }
    else throw "Uknown matcher type";
}
template<typename T>
vector<cv::DMatch> Matcher::calculate(Extractor extractor1, Extractor extractor2, T matcher, const float ratio_thresh) {

    double t =  (double) cv::getTickCount();

    vector<vector<cv::DMatch>> knnMatches;
    matcher.knnMatch(extractor1.getDescriptors(), extractor2.getDescriptors(), knnMatches, 2);
    vector<cv::DMatch> goodMatches;

    //double averageDistance = 0.0;
  
    for (size_t i = 0; i < knnMatches.size(); i++)
    {
      //  averageDistance += knnMatches[i][0].distance;
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance)
        {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    t = (double) cv::getTickCount() - t;
    cout << "[Good Matcher] took "<< fixed  << (float)  t * 1000.0 / (float) cv::getTickFrequency() << "ms" << endl;
    t = (double) cv::getTickCount();
   // vector<cv::DMatch> allMatches;
     //matcher.match(extractor1.getDescriptors(), extractor2.getDescriptors(),allMatches);
    _goodMatchesRatio = (float) goodMatches.size() / (float) knnMatches.size();
    cout << " Good match percentage: " 
        << goodMatches.size() << "/"<<knnMatches.size() << "==" <<  100 * _goodMatchesRatio  << "%" 
        << "%" << endl ;
    
    if(goodMatches.size() > 1) return filter(goodMatches, extractor1, extractor2);
    else return goodMatches;
/*
            int i1 = knnMatches[i][0].queryIdx;
            int i2 = knnMatches[i][0].trainIdx;

            const cv::KeyPoint &kp1 = extractor1.getKeyPoints()[i1], &kp2 = extractor1.getKeyPoints()[i2];*/
            
/*
    for(it1 = matches1.begin();it1 != matches1.end();it1++)
	{	for(it2 =matches2.begin();it2 != matches2.end();it2++)
		{
			if((*it1).queryIdx == (*it2).trainIdx && (*it2).queryIdx == (*it1).trainIdx)
			{
				twoside_matches.push_back(DMatch((*it1).queryIdx,(*it1).trainIdx,(*it1).distance));
				//break;
			}	
		}
	}*/

}

vector<cv::DMatch> Matcher::filter(vector<cv::DMatch> matches, Extractor extractor1, Extractor extractor2) {
    double t =  (double) cv::getTickCount();
  int inliers = 0;
  vector<cv::DMatch> homographyMatches;

        //-- Localize the object
        vector<cv::Point2f> obj;
        vector<cv::Point2f> scene;
        for( size_t i = 0; i < matches.size(); i++ )
        {
            //-- Get the keypoints from the good matches
            obj.push_back( extractor1.getKeyPoints()[ matches[i].queryIdx ].pt );
            scene.push_back( extractor2.getKeyPoints()[ matches[i].trainIdx ].pt );
        }
        cv::Mat homography, mask ;
        int minInliers = 6; //can be any value > 4
        double reprojectionError = 3; // default value, you can change it to some lower to get more reliable estimation.
        homography = cv::findHomography( obj, scene, cv::RANSAC, reprojectionError, mask );
        if(!homography.empty() && !mask.empty()) {    

            for (int i=0; i< mask.rows; ++i)
            {
                if(mask.at<bool>(i, 0)) {
                    homographyMatches.push_back(matches[i]);
                    inliers++;
                }  
            }
            cout << " inliers: " << inliers << " / " << mask.rows << endl;
        }

    t =  (double) cv::getTickCount() - t ;
    cout << "[Homography Matcher] took " <<  fixed << (float)  t * 1000.0 /(float) cv::getTickFrequency() << "ms" << endl;


    _homographyMatchesRatio = (float) homographyMatches.size() / (float) matches.size() ;
    cout << " Filter match percentage: " 
         << 100 * _homographyMatchesRatio
         << "%" << endl ;

    return homographyMatches;
}

float Matcher::getScore() {
    return _homographyMatchesRatio * _goodMatchesRatio;
}
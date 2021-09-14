#include "include/Extractor.h"

#include <iostream>
//#include <numeric>
#include <opencv2/imgproc.hpp> 

using namespace std; 

Extractor::Extractor() {
    _featureDetector = cv::SiftFeatureDetector::create();
    _featureExtractor = cv::SiftDescriptorExtractor::create();
}

Extractor::~Extractor() {
    //delete[] _featureDetector;
   // delete[] _featureExtractor;
}

void Extractor::calcuateSift(cv::Mat& input, int length) {

    double t =  (double) cv::getTickCount();
    cout << "[Extract Feature] Compute SIFT features using opencv sift\n";

    cv::Mat gray; // = input.clone();

    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    
    cv::blur(gray, gray, cv::Size(3, 3));

    //cv::Mat thresh1;
   // cv::Mat thresh2;
   // cv::threshold( gray, gray, 120, 130, 4);
    //cv::adaptiveThreshold(gray, gray, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 2 , 1);
   // cv::threshold( gray, thresh2, 90, 255, 3);

   /* cv::Mat canny;
    cv::Canny( gray, canny, 1, 50 );*/

  /*  vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours( canny, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );


    cv::Mat drawing = cv::Mat::zeros( canny.size(), CV_8UC3);
    cv::RNG rng(12345);
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        cv::drawContours( gray, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
    }
*/

    /*vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );*/


  //  input = gray.clone();

       
    _featureDetector->detect(gray, _keypoints);

   // std::reverse(_keypoints.begin(), _keypoints.end());

   // sort(_keypoints.begin(), _keypoints.end(), [](cv::KeyPoint a, cv::KeyPoint b) { return a.response > b.response; });

   

   /* if(0 != length && length !=  _keypoints.size()) {
        _keypoints = vin::slice(_keypoints, 0, length-1);
    }*/
    

   /* for(auto keypoint : _keypoints) {
        cout << keypoint.angle << endl;
    }*/
    //auto lambda = [](double a, cv::KeyPoint key){ return a + key.angle; };
   // double meanAngle = std::accumulate(_keypoints.begin(), _keypoints.end(), 0.0 /* _keypoints[0].angle*/, lambda) / _keypoints.size();
    
    _featureExtractor->compute(gray, _keypoints, _descriptors);


    t = (double) cv::getTickCount() - t;

    cout << " [Extract Feature Sift]  " 
         << " keypoints: " << _keypoints.size()
         << "; descriptors: " << _descriptors.size()
          << "; took " << t * 1000 / cv::getTickFrequency() << "ms" << endl;


   /* vot::SiftData sift_data;
    //vot::OpencvKeyPoints2libvotSift(cv_keypoints, sift_descriptors, sift_data);

    if (!sift_data.SaveSiftFile(feat_filenames[i])) {
        cerr << "[Extract Feature] sift_data.SaveSiftFile error.\n";
        exit(-1);
    }
    cout << "[Extract Feature] Save sift data (" << sift_data.getFeatureNum()
                << " features) to " <<  feat_filenames[i] << "\n";
    }*/
}

vector<cv::KeyPoint> Extractor::getKeyPoints() {
    
    return _keypoints;
}    
cv::Mat Extractor::getDescriptors() {
    return _descriptors;
}    



/*
bool OpencvKeyPoints2libvotSift(std::vector<cv::KeyPoint> &key_points,
                                cv::Mat &descriptors,
                                SiftData &sift_data)
{
	sift_data.clear();
	int num_features = key_points.size();
	sift_data.setFeatureNum(num_features);
	DTYPE *&dp = sift_data.getDesPointer();
	LTYPE *&lp = sift_data.getLocPointer();

	int des_dim = sift_data.getDesDim();
	int loc_dim = sift_data.getLocDim();
	dp = new DTYPE [num_features * des_dim];
	lp = new LTYPE [num_features * loc_dim];

	for (int i = 0; i < num_features; i++) {
		cv::KeyPoint &kp = key_points[i];
		lp[i*loc_dim + 0] = kp.pt.x;	// x coordinate
		lp[i*loc_dim + 1] = kp.pt.y;	// y coordinate
		lp[i*loc_dim + 2] = 0;			// color (not available)
		lp[i*loc_dim + 3] = kp.size;	// scale
		lp[i*loc_dim + 4] = kp.angle;	// orientation

		// save descriptors
		for (int j = 0; j < des_dim; j++)
			dp[i * des_dim + j] = static_cast<DTYPE>(descriptors.at<float>(i,j));
	}

	return true;
}*/
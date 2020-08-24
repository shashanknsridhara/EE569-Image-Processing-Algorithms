#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>


int main(int argc, const char* argv[])
{
    //Load images as RBG
    const cv::Mat husky1 = cv::imread("Husky_1.jpg");
    const cv::Mat husky2 = cv::imread("Husky_2.jpg");
    const cv::Mat husky3 = cv::imread("Husky_3.jpg");
    const cv::Mat puppy1 = cv::imread("Puppy_1.jpg");

    //Define SIFT discriptor
    cv::SiftFeatureDetector detector;
    std::vector<cv::KeyPoint> keypoints1, keypoints2, keypoints3, keypoints4;

    //detect the keypoints in each image
    detector.detect(husky1, keypoints1);
    detector.detect(husky2, keypoints2);
    detector.detect(husky3, keypoints3);
    detector.detect(puppy1, keypoints4);
    
    //extract the feature descriptors of each image
    SiftFeatureDetector extractor;
    const Mat descriptor1, descriptor2, descriptor3, descriptor4;
    
    detector.detect(husky1, keypoints1);
    detector.detect(husky2, keypoints2);
    detector.detect(husky3, keypoints3);
    detector.detect(puppy1, keypoints4);



    // Add results to image and save.


    return 0;
}
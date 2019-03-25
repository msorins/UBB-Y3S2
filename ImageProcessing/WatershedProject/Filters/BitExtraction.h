//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef BIT_EXTRACTION
#define BIT_EXTRACTION


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>

using namespace cv;
using namespace std;
class BitExtraction: public FilterInterface {
public:
    BitExtraction() : FilterInterface("L2: Bit Extraction") {

    }

    Mat processImage(Mat image) override {
        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                image.at<cv::Vec3b>(i,j)[0] &= 224;
                image.at<cv::Vec3b>(i,j)[1] &= 224;
                image.at<cv::Vec3b>(i,j)[2] &= 224;

            }
        }

        return image;
    }
};

#endif
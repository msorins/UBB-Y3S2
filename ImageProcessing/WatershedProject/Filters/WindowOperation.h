//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_FILTER_L2
#define COLOR_FILTER_L2


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>

using namespace cv;
using namespace std;
class NegativeOfImage: public FilterInterface {
public:
    NegativeOfImage() : FilterInterface("NegativeOfImage") {

    }

    Mat processImage(Mat image) override {

        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                image.at<cv::Vec3b>(i,j)[0] = 255 - image.at<cv::Vec3b>(i,j)[0];
                image.at<cv::Vec3b>(i,j)[1] = 255 - image.at<cv::Vec3b>(i,j)[1];
                image.at<cv::Vec3b>(i,j)[2] = 255 - image.at<cv::Vec3b>(i,j)[2];

            }
        }

        return image;
    }
};

#endif
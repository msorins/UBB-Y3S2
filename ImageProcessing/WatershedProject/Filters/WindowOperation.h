//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef WINDOW_OPERATION
#define WINDOW_OPERATION


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>

using namespace cv;
using namespace std;
class WindowOperation: public FilterInterface {
public:
    WindowOperation() : FilterInterface("L2: Window Operation") {

    }

    Mat processImage(Mat image) override {
        int a = 100;
        int b = 200;
        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                if( image.at<cv::Vec3b>(i,j)[0]  < a ||  image.at<cv::Vec3b>(i,j)[0]  > b) {
                    image.at<cv::Vec3b>(i,j)[0] = 0;
                    image.at<cv::Vec3b>(i,j)[1] = 0;
                    image.at<cv::Vec3b>(i,j)[2] = 0;
                }

            }
        }

        return image;
    }
};

#endif
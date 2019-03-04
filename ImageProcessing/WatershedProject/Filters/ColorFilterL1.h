//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_FILTER_L1
#define COLOR_FILTER_L1

#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>

using namespace cv;
using namespace std;
class ColorFilterL1: public FilterInterface {
public:
    ColorFilterL1() : FilterInterface("ColorFilterL1") {

    }

    Mat processImage(Mat image) override {

        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                if((i + j) % 2 == 0) {
                    image.at<cv::Vec3b>(i,j)[0] /= 2;
                    image.at<cv::Vec3b>(i,j)[1] /= 2;
                    image.at<cv::Vec3b>(i,j)[2] /= 2;
                } else {
                    image.at<cv::Vec3b>(i,j)[0] *= 2;
                    image.at<cv::Vec3b>(i,j)[1] *= 2;
                    image.at<cv::Vec3b>(i,j)[2] *= 2;
                }

            }
        }

        return image;
    }
};

#endif
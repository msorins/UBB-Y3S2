//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_RGB_TO_HSL
#define COLOR_RGB_TO_HSL


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>
#include <vector>
#include <queue>
#include <opencv/cv.hpp>

#define ZERO 0
#define ONE 255
#define STEP 1

using namespace cv;
using namespace std;
class RGBtoHSL: public FilterInterface {
public:
    RGBtoHSL() : FilterInterface("L6: RGB to HSL") {

    }

    Mat processImage(Mat image) override {
        Mat hsvIMG;

        auto manualHSV = imageRGBtoHSV(image);
        return manualHSV;
    }

    void pixelRGBtoHSV(double r, double g, double b, double &h, double &s, double &v)
    {
        v = max(max(r, g), b);
        double t = min(min(r, g), b);
        double delta = v - t;
        if (v != 0.0)
            s = delta / v;
        else
            s = 0.0;
        if (s == 0.0)
            h = 0.0;
        else
        {
            if (r == v)
                h = (g - b) / delta;
            else
            if (g == v)
                h = 2.0 + (b - r) / delta;
            else
            if (b == v)
                h = 4.0 + (r - g) / delta;
            h = h * 60.0;
            if (h < 0.0)
                h += 360;
        }
    }

    Mat imageRGBtoHSV(Mat image) {
        Mat hsvImage = image.clone();

        for(int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                double h, s, v;
                pixelRGBtoHSV(image.at<cv::Vec3b>(i, j)[0],  image.at<cv::Vec3b>(i, j)[1],  image.at<cv::Vec3b>(i, j)[2],
                              h, s, v
                             );

                hsvImage.at<cv::Vec3b>(i, j)[0] = h;
                hsvImage.at<cv::Vec3b>(i, j)[1] = s;
                hsvImage.at<cv::Vec3b>(i, j)[2] = v;
            }
        }
        return hsvImage;
    }

    string type2str(int type) {
        string r;

        uchar depth = type & CV_MAT_DEPTH_MASK;
        uchar chans = 1 + (type >> CV_CN_SHIFT);

        switch ( depth ) {
            case CV_8U:  r = "8U"; break;
            case CV_8S:  r = "8S"; break;
            case CV_16U: r = "16U"; break;
            case CV_16S: r = "16S"; break;
            case CV_32S: r = "32S"; break;
            case CV_32F: r = "32F"; break;
            case CV_64F: r = "64F"; break;
            default:     r = "User"; break;
        }

        r += "C";
        r += (chans+'0');

        return r;
    }
};

#endif
//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_THINNING
#define COLOR_THINNING


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>
#include <vector>
#include <queue>

#define ZERO 0
#define ONE 255
#define NO_CARE -1

using namespace cv;
using namespace std;
class Thinning: public FilterInterface {
public:
    Thinning(): FilterInterface("L4: c) Thinning") {

    }

    Mat processImage(Mat image) override {
        // Remove the noise from image
        image = removeNoise(image);

        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply threshold
        image = thresholdOtsu(image);

        return doThinning(image);
    }

    Mat makeImageGrayScale(Mat image) {
        Mat grayScale(image.rows, image.cols, CV_8UC1, Scalar(70));

        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                double gray = 0.21 * image.at<cv::Vec3b>(i,j)[0] +
                              0.72 * image.at<cv::Vec3b>(i,j)[1] +
                              0.07 * image.at<cv::Vec3b>(i,j)[2];
                grayScale.at<uchar>(i,j) = (uchar) gray;
            }
        }

        return grayScale;
    }

    Mat thresholdOtsu(Mat image) {
        threshold(image, image, ZERO, ONE, CV_THRESH_BINARY | CV_THRESH_OTSU);
        return image;
    }

    Mat removeNoise(Mat image) {
        for(int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                if (((int) image.at<cv::Vec3b>(i, j)[0]) != ZERO && (int) image.at<cv::Vec3b>(i, j)[0] != ONE) {
                    int val = image.at<cv::Vec3b>(i, j)[0];
                    if(abs(val - ZERO) <= abs(val - ONE) ) {
                        image.at<cv::Vec3b>(i, j)[0] = ZERO;
                        image.at<cv::Vec3b>(i, j)[1] = ZERO;
                        image.at<cv::Vec3b>(i, j)[2] = ZERO;
                    } else {
                        image.at<cv::Vec3b>(i, j)[0] = ONE;
                        image.at<cv::Vec3b>(i, j)[1] = ONE;
                        image.at<cv::Vec3b>(i, j)[2] = ONE;
                    }
                }
            }
        }

        return image;
    }

    Mat doThinning(Mat image) {
//        vector<vector< vector<int> >> kernels = {
//                { {ZERO, ZERO, ZERO}, {NO_CARE, ONE, NO_CARE}, {ONE, ONE, ONE} },
//                { {NO_CARE, ZERO, ZERO}, {ONE, ONE, ZERO}, {NO_CARE, ONE, NO_CARE} },
//                { {ONE, NO_CARE, ZERO}, {ONE, ONE, ZERO}, {ONE, NO_CARE, ZERO} },
//                { {NO_CARE, ONE, NO_CARE}, {ONE, ONE, ZERO}, {NO_CARE, ZERO, ZERO} },
//                { {ONE, ONE, ONE}, {NO_CARE, ONE, NO_CARE}, {ZERO, ZERO, ZERO} },
//                { {NO_CARE, ONE, NO_CARE}, {ZERO, ONE, ONE}, {ZERO, ZERO, NO_CARE} },
//                { {ZERO, NO_CARE, ONE}, {ZERO, ONE, ONE}, {ZERO, NO_CARE, ONE} },
//                { {ZERO, ZERO, NO_CARE}, {ZERO, ONE, ONE}, {NO_CARE, ONE, NO_CARE} }
//        };

        vector<vector< vector<int> >> kernels = {
                { {ZERO, ZERO, ZERO}, {NO_CARE, ONE, ZERO}, {ONE, ONE, ONE} },
                { {NO_CARE, ZERO, ZERO}, {ONE, ONE, ZERO}, {ONE, ONE, NO_CARE} },
                { {ONE, NO_CARE, ZERO}, {ONE, ONE, ZERO}, {ONE, NO_CARE, ZERO} },
                { {ONE, ONE, NO_CARE}, {ONE, ONE, ZERO}, {ONE, ZERO, ZERO} },
                { {ONE, ONE, ONE}, {NO_CARE, ONE, NO_CARE}, {ZERO, ZERO, ZERO} },
                { {NO_CARE, ONE, ONE}, {ZERO, ONE, ONE}, {ZERO, ZERO, NO_CARE} },
                { {ZERO, NO_CARE, ONE}, {ZERO, ONE, ONE}, {ZERO, NO_CARE, ONE} },
                { {ZERO, ZERO, NO_CARE}, {ZERO, ONE, ONE}, {NO_CARE, ONE, ONE} }
        };


        // Loop through the kernels
        bool changed = true;
        int it = 0;
        while(changed) {
            changed = false;
            Mat resultImage = image;

            for(vector<vector<int>> const &kernel: kernels) {
                for(int i = 0; i < image.rows - 3; i++) {
                    for(int j = 0; j < image.cols - 3; j++) {
                        int points = 0;

                        for(int fx = 0; fx < 3; fx++) {
                            for(int fy = 0; fy < 3; fy++) {
                                if(kernel[fx][fy] == NO_CARE) {
                                    points++;
                                    continue;
                                }

                                if( (int) kernel[fx][fy] ==  (int) image.at<uchar>(i + fx, j + fy)  )  {
                                    points++;
                                }
                            }
                        }
                        if(points == 9) {
                            resultImage.at<uchar>(i + 1, j + 1) = ZERO;
                            changed = true;
                        }
                    }
                }
            }
            if(changed) {
                image = resultImage;
//                return image;
            }

            it++;
            if(it == 100){
                return image;
            }

        }

        return image;
    }
};

#endif
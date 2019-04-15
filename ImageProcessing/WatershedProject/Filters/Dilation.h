//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_DILATION
#define COLOR_DILATION


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
class Dilation: public FilterInterface {
public:
    Dilation(): FilterInterface("L5: b) Dilation") {

    }

    Mat processImage(Mat image) override {
        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply threshold
        image = thresholdOtsu(image);

        // Apply dilation a few times
        vector< vector<int> > erosionTargetFive{{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1} };
        for(int _ = 0; _ < 5; _++) {
            image = dilation(image, erosionTargetFive);
        }

        return image;
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

    Mat dilation(Mat image, vector<vector<int> > kernel) {
        int n = kernel.size();
        int m = kernel[0].size();

        vector< vector < bool> > shouldBeOneImage(image.rows, vector<bool>(image.cols, false));
        for(int i = n / 2; i < image.rows - n / 2; i++) {
            for(int j = m / 2; j < image.cols - m / 2; j++) {

                // Loop the kernel
                if( (int) image.at<uchar>(i, j) == ZERO) {
                    bool shouldBeOne = false;
                    for(int crtX = i - n / 2, x = 0; crtX <= i + n / 2; crtX++, x++) {
                        for(int crtY = j - m / 2, y = 0; crtY <= j + m / 2; crtY++, y++) {
                            if((int) image.at<uchar>(crtX, crtY) == ONE && kernel[x][y] == 1) {
                                shouldBeOne = true;
                                break;
                            }
                        }
                    }

                    if(shouldBeOne) {
                        shouldBeOneImage[i][j] = true;
                    }
                }
            }
        }

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                if(shouldBeOneImage[i][j]) {
                    image.at<uchar>(i, j) = ONE;
                }
            }
        }

        return image;
    }
};

#endif
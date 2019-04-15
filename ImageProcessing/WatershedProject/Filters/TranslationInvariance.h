//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_TRANSLATION_INVARIANCE
#define COLOR_TRANSLATION_INVARIANCE


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include <queue>
#include <opencv/cv.hpp>

#define ZERO 0
#define ONE 255
#define STEP 1

using namespace cv;
using namespace std;
class TranslationInvariance: public FilterInterface {
public:
    TranslationInvariance(): FilterInterface("L5: e) Translation Invariance") {

    }

    Mat processImage(Mat image) override {
        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply threshold
        image = thresholdOtsu(image);

        vector< vector<int> > erosionTargetFive{{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1} };

        // ImageA => erosion -> translation
        auto imageA = erosion(image.clone(), erosionTargetFive);
        imageA = translation(imageA, 0, 25);

        // ImageB => translation -> erosion
        auto imageB = translation(image.clone(), 0, 25);
        imageB = erosion(imageB, erosionTargetFive);

        imshow("imageA", imageA);
        imshow("imageB", imageB);

        // Compute Difference image
        return diffImage(imageA, imageB);
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

    Mat erosion(Mat image, vector< vector <int> > kernel) {
        int n = kernel.size();
        int m = kernel[0].size();

        vector< vector < bool> > shouldBeZeroImage(image.rows, vector<bool>(image.cols, false));
        for(int i = n / 2; i < image.rows - n / 2; i++) {
            for(int j = m / 2; j < image.cols - m / 2; j++) {

                // Loop the kernel
                if( (int) image.at<uchar>(i, j) == ONE) {
                    bool shouldBeZero = false;
                    for(int crtX = i - n / 2, x = 0; crtX <= i + n / 2; crtX++, x++) {
                        for(int crtY = j - m / 2, y = 0; crtY <= j + m / 2; crtY++, y++) {
                            if((int) image.at<uchar>(crtX, crtY) == ZERO && kernel[x][y] == 1) {
                                shouldBeZero = true;
                                break;
                            }
                        }
                    }

                    if(shouldBeZero) {
                        shouldBeZeroImage[i][j] = true;
                    }
                }
            }
        }

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                if(shouldBeZeroImage[i][j]) {
                    image.at<uchar>(i, j) = ZERO;
                }
            }
        }

        return image;
    }

    Mat translation(Mat image, int translationX, int translationY) {
        Mat translatedImage(image.rows, image.cols, CV_8UC1, Scalar(0));

        for(int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                translatedImage.at<uchar>( (i + translationX) % image.rows, (j + translationY) % image.cols ) = image.at<uchar>(i, j);
            }
        }

        return translatedImage;
    }

    Mat diffImage(Mat imageA, Mat imageB) {
        Mat diffImage(imageA.rows, imageA.cols, CV_8UC1, Scalar(0));

        for(int i = 0; i < imageA.rows; i++) {
            for (int j = 0; j < imageA.cols; j++) {
                diffImage.at<uchar>( i, j ) =  abs((int) imageA.at<uchar>(i, j) - (int) imageB.at<uchar>(i, j));
                assert((int) diffImage.at<uchar>(i, j) == 0);
            }
        }

        return diffImage;
    }
};

#endif
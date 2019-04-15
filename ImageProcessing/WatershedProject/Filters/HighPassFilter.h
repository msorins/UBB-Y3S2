//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_HIGH_PASS
#define COLOR_HIGH_PASS


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
class HighPassFilter: public FilterInterface {
public:
    HighPassFilter(): FilterInterface("L3: HighPassFilter") {

    }

    Mat processImage(Mat image) override {
        image = makeImageGrayScale(image);
        Mat resultImage = image.clone();

//        vector<vector<float>> kernel = { {0, -1, 0}, {-1, 4, -1}, {0, -1, 0} };
//        vector<vector<float>> kernel = { {0, -0.25f, 0}, {-0.25f, 4, -0.25f}, {0, -0.25f, 0} };
        vector<vector<float>> kernel = { {(float)-1/9, (float)-1/9, (float)-1/9}, {(float)-1/9, (float)8/9, (float)-1/9}, {(float)-1/9, (float)-1/9, (float)-1/9} };

        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
               float val = 0;

                for(int imX = i - 1, kerX = 0; imX <= i + 1; imX++, kerX++) {
                    for(int imY = j - 1, kerY = 0; imY <= j + 1; imY++, kerY++) {
                        if(imX < 0 || imY < 0 || imX >= image.rows || imY >= image.cols) {
                            continue;
                        }

                        float x = (float) image.at<uchar>(imX, imY);
                        float y = kernel[kerX][kerY];
                        val +=  (x * y) ;
                    }
                }
                resultImage.at<uchar>(i,j) = min(val, (float)255);
            }
        }

       return resultImage;
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
};

#endif
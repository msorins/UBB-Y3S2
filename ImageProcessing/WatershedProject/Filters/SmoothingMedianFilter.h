//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_SMOOTHING
#define COLOR_SMOOTHING


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>
#include <vector>
#include <queue>
#include <opencv/cv.hpp>
#include <algorithm>

#define ZERO 0
#define ONE 255
#define STEP 1

using namespace cv;
using namespace std;

class SmoothingMedianFilter : public FilterInterface {
public:
    SmoothingMedianFilter() : FilterInterface("L5: c) SmoothingMedianFilter") {

    }

    Mat processImage(Mat image) override {
        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply dilation a few times
        vector<vector<int> > targetFive{{1, 1, 1, 1, 1},
                                        {1, 1, 1, 1, 1},
                                        {1, 1, 1, 1, 1},
                                        {1, 1, 1, 1, 1},
                                        {1, 1, 1, 1, 1}};
        image = smoothing(image, targetFive);

        return image;
    }

    Mat makeImageGrayScale(Mat image) {
        Mat grayScale(image.rows, image.cols, CV_8UC1, Scalar(70));

        for (int i = 0; i < image.rows; i++) {

            for (int j = 0; j < image.cols; j++) {
                double gray = 0.21 * image.at<cv::Vec3b>(i, j)[0] +
                              0.72 * image.at<cv::Vec3b>(i, j)[1] +
                              0.07 * image.at<cv::Vec3b>(i, j)[2];
                grayScale.at<uchar>(i, j) = (uchar) gray;
            }
        }

        return grayScale;
    }

    Mat smoothing(Mat image, vector<vector<int> > kernel) {
        int n = kernel.size();
        int m = kernel[0].size();

        vector<vector<bool> > shouldBeOneImage(image.rows, vector<bool>(image.cols, false));
        for (int i = n / 2; i < image.rows - n / 2; i++) {
            for (int j = m / 2; j < image.cols - m / 2; j++) {

                // Loop the kernel
                bool shouldBeOne = false;
                vector<int> values;
                for (int crtX = i - n / 2, x = 0; crtX <= i + n / 2; crtX++, x++) {
                    for (int crtY = j - m / 2, y = 0; crtY <= j + m / 2; crtY++, y++) {
                        if(kernel[x][y] == 1) {
                            values.push_back( (int) image.at<uchar>(crtX, crtY) );
                        }
                    }
                }

                sort(values.begin(), values.end());
                image.at<uchar>(i, j) = static_cast<uchar>(values[values.size() / 2 ]);
            }
        }

        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                if (shouldBeOneImage[i][j]) {
                    image.at<uchar>(i, j) = ONE;
                }
            }
        }

        return image;
    }
};

#endif
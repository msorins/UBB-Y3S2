//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_CONTOUR
#define COLOR_CONTOUR


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>
#include <vector>

#define ZERO 0
#define ONE 255

using namespace cv;
using namespace std;
class Contour: public FilterInterface {
public:
    Contour(): FilterInterface("L4: a) Contur") {

    }

    Mat processImage(Mat image) override {
        // Remove Noise from Image
        image = removeNoise(image);

        // Create contour for blacks
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};


        vector< vector<bool> > changed(image.rows, vector<bool>(image.cols, false));
        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                auto x = image.at<cv::Vec3b>(i,j)[0];
                auto y = image.at<cv::Vec3b>(i,j)[1];
                auto z = image.at<cv::Vec3b>(i,j)[2];

                if(x == 255 && y == 255 && z == 255) {
                    bool isContour = false;
                    for(int h = 0; h < 4; h++) {
                        int crtX = i + dx[h];
                        int crtY = j + dy[h];

                        if(crtX < 0 || crtY < 0 || crtX >= image.rows || crtY >= image.cols) {
                            continue;
                        }

                        if(changed[crtX][crtY]) {
                            continue;
                        }

                        if(image.at<cv::Vec3b>(crtX,crtY)[0] != 255 ||  image.at<cv::Vec3b>(crtX,crtY)[1] != 255  || image.at<cv::Vec3b>(crtX,crtY)[2] != 255 ) {
                            isContour = true;
                            break;
                        }
                    }

                    if(isContour) {
                        image.at<cv::Vec3b>(i,j)[0] = 0;
                        image.at<cv::Vec3b>(i,j)[1] = 0;
                        image.at<cv::Vec3b>(i,j)[2] = 255;
                        changed[i][j] = true;
                    }
                }
            }
        }

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
};

#endif
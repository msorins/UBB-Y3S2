//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef WATERSHED_FILTER_L2
#define WATERSHED_FILTER_L2


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FilterInterface.h"
#include <iostream>
#include <queue>
using namespace cv;
using namespace std;

#define ZERO 0
#define ONE 254
#define STEP 3

class WaterShedFilter: public FilterInterface {
public:
    WaterShedFilter() : FilterInterface("WaterShedFilter") {

    }

    Mat processImage(Mat image) override {
        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply threshold
        image = thresholdOtsu(image);

        // Inverse pixels
        image = inverseImage(image);

        // Erode foreground
        vector< vector<int> > erosionTarget{{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
        vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
        image = erosion(image, erosionTargetThree);
        image = erosion(image, erosionTargetThree);

        // Apply distance transform
        image = distanceTransform(image);

        // Watershed


        // Return image with contours
        return image;
    }

private:
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

    Mat distanceTransform(Mat image) {
        queue<int> qx, qy;
        vector<int> dx{-1, 1, 0, 0, -1, -1, 1, 1};
        vector<int> dy{0, 0, -1, 1, -1,  1, 1, -1};

        vector< vector<bool> > visited(image.rows, vector<bool>(image.cols, false));

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                if(image.at<uchar>(i, j) != ZERO) {
                    continue;
                }

                for(int h = 0; h < 4; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols ) {
                        continue;
                    }

                    if( !visited[nextX][nextY] && (int) image.at<uchar>(nextX, nextY) == ONE ) {
                        visited[nextX][nextY] = true;
                        image.at<uchar>(nextX, nextY) = 100;
                        qx.push(nextX);
                        qy.push(nextY);
                    }
                }
            }
        }

        while(!qx.empty()) {
            int crtX = qx.front(); qx.pop();
            int crtY = qy.front(); qy.pop();

            bool isBigger = true;
            for(int h = 0; h < 8; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols || (int) image.at<uchar>(nextX, nextY) == ZERO ) {
                    continue;
                }

                if( (int) image.at<uchar>(crtX, crtY) <= (int) image.at<uchar>(nextX, nextY)) {
                    isBigger = false;
                }

                if( (int) image.at<uchar>(crtX, crtY) + STEP < (int) image.at<uchar>(nextX, nextY) ) {
                    visited[nextX][nextY] = true;
                    image.at<uchar>(nextX, nextY) = (uchar) min((image.at<uchar>(crtX, crtY) + STEP), 254);
                    qx.push(nextX);
                    qy.push(nextY);
                }
            }

            if(isBigger) {
                cout << "Peak: " << crtX << " " << crtY << " ; val: " << (int) image.at<uchar>(crtX, crtY) << "\n";
            }


        }
        return image;
    }

    Mat inverseImage(Mat image) {
        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                if( (int) image.at<uchar>(i,j) == ZERO ) {
                    image.at<uchar>(i,j) = ONE;
                } else {
                    image.at<uchar>(i,j) = ZERO;
                }
            }
        }

        return image;
    }

    Mat erosion(Mat image, vector< vector <int> > target) {
        /*
         * target = square matrix
         */
        int n = target.size();
        int m = target[0].size();

        vector< vector < bool> > shouldBeZeroImage(image.rows, vector<bool>(image.cols, false));
        for(int i = n / 2; i < image.rows - n / 2; i++) {
            for(int j = m / 2; j < image.cols - m / 2; j++) {

                // Loop the target
                if( (int) image.at<uchar>(i, j) == ONE) {
                    bool shouldBeZero = false;
                    for(int crtX = i - n / 2, x = 0; crtX <= i + n / 2; crtX++, x++) {
                        for(int crtY = j - m / 2, y = 0; crtY <= j + m / 2; crtY++, y++) {
                            if((int) image.at<uchar>(crtX, crtY) == ZERO && target[x][y] == 1) {
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
};

/*
 * 0 0 0 1 1 1 1
 * 0 0 1 1 1 1 1
 * 0 1 1 1 1 1 0
 * 0 0 1 1 1 1 0
 * 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0
 *
 *
 * 0 0 0 1 1 1 1
 * 0 0 0 z 1 1 1
 * 0 1 1 1 1 1 0
 * 0 0 1 1 1 1 0
 * 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0
 */
#endif
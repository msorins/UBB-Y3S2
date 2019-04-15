//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef COLOR_SKELETON
#define COLOR_SKELETON


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
#define STEP 1

using namespace cv;
using namespace std;
class Skeleton: public FilterInterface {
public:
    Skeleton(): FilterInterface("L4: b) Skeleton") {

    }

    Mat processImage(Mat image) override {
        // Remove the noise from image
        image = removeNoise(image);

        // Make image grayscale
        image = makeImageGrayScale(image);

        // Apply threshold
        image = thresholdOtsu(image);

        vector<Point> markers;
        image = distanceTransform(image, markers);

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

    Mat distanceTransform(Mat image, vector<Point> &markers) {
        vector< vector<double> > distanceMap(image.rows, vector<double>(image.cols, 0));
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
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
                        image.at<uchar>(nextX, nextY) = 50;
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
            for(int h = 0; h < 4; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols || (int) image.at<uchar>(nextX, nextY) == ZERO ) {
                    continue;
                }

                if( (int) image.at<uchar>(crtX, crtY) < (int) image.at<uchar>(nextX, nextY)) {
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
                markers.push_back(Point(crtX, crtY));
                markerImage.at<Vec3b>(crtX, crtY) = {0, 255, 0};
            }
        }
        return markerImage;
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
//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef WATERSHED_FILTER_Proj
#define WATERSHED_FILTER_Proj


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
#define STEP 1

struct Pixel {
    int val;
    int x;
    int y;

    Pixel(int val, int x, int y) : val(val), x(x), y(y) {}

    friend ostream &operator<<(ostream &os, const Pixel &pixel) {
        os << "val: " << pixel.val << " x: " << pixel.x << " y: " << pixel.y;
        return os;
    }
};

class Comp {
public:
    bool operator()(Pixel A, Pixel B) {
        return A.val < B.val;
    }
};

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
        vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
        image = erosion(image, erosionTargetThree);
        image = erosion(image, erosionTargetThree);

        // Apply distance transform
        vector<Point> markers;
        image = distanceTransform(image, markers);
        Mat distanceImage = image;
        cout << "Detected " << markers.size() << " markers \n";

        // Watershed
        if(markers.size() == 0) {
            markers.push_back(Point(627, 414));
            image.at<uchar>(627,414) = 25;
        }
        
        image = watershed(image, markers);
//        for(int i = 0; i < image.rows; i++) {
//            for(int j = 0; j < image.cols; j++) {
//                if((int) distanceImage.at<uchar>(i,j) != 0 && image.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[1] == 0 && image.at<Vec3b>(i, j)[1] == 0) {
//                    markers.clear();
//                    markers.push_back(Point(i, j));
//                    distanceImage.at<uchar>(i,j) = 25;
//                    image = watershed(image, markers);
//                    return image;
//                }
//            }
//        }

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
                markers.push_back(Point(crtX, crtY));
                markerImage.at<Vec3b>(crtX, crtY) = {0, 255, 0};
            }
        }
        imshow("Distance: ", image);
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

    Mat watershed(Mat image, vector<Point> const &markers) {
        priority_queue<Pixel, vector<Pixel>, Comp> pq;
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
            vector<Vec3b> colors{ {0, 0, 0} };
            for(int i = 1; i < markers.size(); i++) {
            Vec3b vec;
            vec[0] = random(0, 254);
            vec[1] = random(0, 254);
            vec[2] = random(0, 254);
            colors.push_back(vec);
        }
        vector<vector<int>> markerMap(image.rows, vector<int>(image.cols, 0));
        vector<vector<bool>> inPq(image.rows, vector<bool>(image.cols, false));
        vector<int> dx{-1, 1, 0, 0, -1, -1, 1, 1};
        vector<int> dy{0, 0, -1, 1, -1,  1, 1, -1};

        // Put markers in priority queue
        int id = 1;
        for(auto marker: markers) {
            markerMap[marker.x][marker.y] = id;
            for(int i = 0; i < 4; i++) {

                int newX = marker.x + dx[i];
                int newY = marker.y + dy[i];
                if(newX < 0 || newY < 0 || newX >= image.rows || newY >= image.cols) {
                    continue;
                }
                pq.push( Pixel( (int) image.at<uchar>(newX, newY), newX, newY) );
            }
            id++;
        }

        // Do the watershed
        while(!pq.empty()) {
            Pixel top = pq.top(); pq.pop();

            bool canLabel = true;
            int neighboursLabel = 0;
            for(int i = 0; i < 4; i++) {
                int nextX = top.x + dx[i];
                int nextY = top.y + dy[i];
                if(nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols) {
                    continue;
                }
                Pixel next = Pixel( (int) image.at<uchar>(nextX, nextY), nextX, nextY);

                // Must check if all surrounding marked have the same color
                if(markerMap[next.x][next.y] != 0 && next.val != 0) {
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap[next.x][next.y];
                    } else {
                        if(markerMap[next.x][next.y] != neighboursLabel ) {
                            canLabel = false;
                        }
                    }
                } else {
                    if(inPq[nextX][nextY] == false) {
                        inPq[next.x][next.y] = true;
                        pq.push(next);
                    }
                }
            }

            if(canLabel) {
                markerMap[top.x][top.y] = neighboursLabel;
            }
        }

        // Transform markerMap into an image
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                markerImage.at<Vec3b>(i, j) = colors[ markerMap[i][j] ];
            }
        }

        return markerImage;
    }


    int random(int min, int max) //range : [min, max)
    {
        static bool first = true;
        if (first)
        {
            srand( time(NULL) ); //seeding for the first time only!
            first = false;
        }
        return min + rand() % (( max + 1 ) - min);
    }

    Mat bitwiseAnd(Mat originalImage, Mat segmentationImage) {
        for(int i = 0; i < originalImage.rows; i++) {
            for(int j = 0; j < originalImage.cols; j++) {
                if((int) segmentationImage.at<uchar>(i, j) == 0) {
                    originalImage.at<Vec3b>(i,j)[0] = 0;
                    originalImage.at<Vec3b>(i,j)[1] = 0;
                    originalImage.at<Vec3b>(i,j)[2] = 0;
                }
            }
        }

        return originalImage;
    }
};

#endif
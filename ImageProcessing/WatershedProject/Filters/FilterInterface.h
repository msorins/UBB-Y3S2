//
// Created by Sorin Sebastian Mircea on 03/03/2019.
//

#ifndef FILTER_INTERFACE
#define FILTER_INTERFACE


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

class FilterInterface {
private:
    string name;

public:
    virtual Mat processImage(Mat image) = 0;

    const string &getName() const {
        return name;
    }

    FilterInterface(const string &name) : name(name) {}
};

#endif
//
// Created by Sorin Sebastian Mircea on 04/03/2019.
//

#ifndef WATERSHEDPROJECT_UTILS_H
#define WATERSHEDPROJECT_UTILS_H

#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QtGui/QPixmap>
#include "../Filters/NegativeOfImage.h"
#include "../Filters/WaterShedFilter.h"
#include "../Filters/WindowOperation.h"
#include "../Filters/BitExtraction.h"
#include "../Filters/Contour.h"
#include "../Filters/Skeleton.h"
#include "../Filters/Thinning.h"
#include "../Filters/Erosion.h"
#include "../Filters/Dilation.h"
#include "../Filters/SmoothingMedianFilter.h"
#include "../Filters/Translation.h"
#include "../Filters/TranslationInvariance.h"
#include "../Filters/RGBtoHSL.h"
#include "../Filters/HighPassFilter.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace cv;
using namespace std;

class Utils {
public:
    static QPixmap fromMat(Mat img) {
        Mat imgNew;
        if(img.channels() == 3) {
            cvtColor(img, imgNew, CV_BGR2RGB);
        } else {
            cvtColor(img, imgNew, CV_GRAY2RGB);
        }
        return QPixmap::fromImage(QImage(imgNew.data, imgNew.cols, imgNew.rows, imgNew.step, QImage::Format_RGB888));
    }

    static vector<FilterInterface*> getFilters() {
        vector<FilterInterface*> filters;
        FilterInterface *f0 = new WaterShedFilter();
        FilterInterface *f1 = new ColorFilterL1();
        FilterInterface *f2 = new NegativeOfImage();
        FilterInterface *f3 = new WindowOperation();
        FilterInterface *f4 = new BitExtraction();
        FilterInterface *f5 = new HighPassFilter();
        FilterInterface *f6 = new Contour();
        FilterInterface *f7 = new Skeleton();
        FilterInterface *f8 = new Thinning();
        FilterInterface *f9 = new Erosion();
        FilterInterface *f10 = new Dilation();
        FilterInterface *f11 = new SmoothingMedianFilter();
        FilterInterface *f12 = new Translation();
        FilterInterface *f13 = new TranslationInvariance();
        FilterInterface *f14 = new RGBtoHSL();
        filters.push_back(f1);
        filters.push_back(f0);
        filters.push_back(f2);
        filters.push_back(f3);
        filters.push_back(f4);
        filters.push_back(f5);
        filters.push_back(f6);
        filters.push_back(f7);
        filters.push_back(f8);
        filters.push_back(f9);
        filters.push_back(f10);
        filters.push_back(f11);
        filters.push_back(f12);
        filters.push_back(f13);
        filters.push_back(f14);
        return filters;
    }

    static vector<string> getImages() {
        string path("../images");
        return get_file_list(path);
    }

private:
    static vector<string> get_file_list(const std::string& path)
    {
        vector<string> fileList;
        if (!path.empty())
        {
            namespace fs = boost::filesystem;

            fs::path apk_path(path);
            fs::recursive_directory_iterator end;

            for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
            {
                const fs::path cp = (*i);
                fileList.push_back(cp.string());
            }
        }
        return fileList;
    }
};

#endif //WATERSHEDPROJECT_UTILS_H
